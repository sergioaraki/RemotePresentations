#include <pebble.h>

static Window *window;
ActionBarLayer *action_bar;
GBitmap *nextIcon;
GBitmap *prevIcon;
GBitmap *timerIcon;
TextLayer *text_layer;

static double elapsed_time = 0;
static bool started = false;
static AppTimer* update_timer = NULL;

enum {
  KEY_DIR = 0x0,
};

void stop_timer() {
  started = false;
    if(update_timer != NULL) {
        app_timer_cancel(update_timer);
        update_timer = NULL;
    }
}

void update_time() {
    static char big_time[] = "00:00:00";
    
    int seconds = (int)elapsed_time % 60;
    int minutes = (int)elapsed_time / 60 % 60;
    int hours = (int)elapsed_time / 3600;

    if(hours > 99) {
        stop_timer();
        return;
    }
  
    snprintf(big_time, 10, "%02d:%02d:%02d", hours, minutes, seconds);

    text_layer_set_text(text_layer, big_time);
}

void handle_timer(void* data) {
  if(started) {
    elapsed_time = elapsed_time+1;
    update_timer = app_timer_register(1000, handle_timer, NULL);
  }
  update_time();
}

void start_timer() {
  started = true;
  update_timer = app_timer_register(1000, handle_timer, NULL);
}
static void set_dir_msg(int dir) {
  Tuplet dir_tuple = TupletInteger(KEY_DIR, dir);

  DictionaryIterator *iter;
  app_message_outbox_begin(&iter);

  if (iter == NULL) {
    return;
  }

  dict_write_tuplet(iter, &dir_tuple);
  dict_write_end(iter);

  app_message_outbox_send();
}

static void down_click_handler(ClickRecognizerRef recognizer, void *context) {
    set_dir_msg(1);
}

static void up_click_handler(ClickRecognizerRef recognizer, void *context) {
    set_dir_msg(0);
}

static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
    if(started) {
        stop_timer();
    } else {
        start_timer();
    }
}

void click_config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_UP, (ClickHandler) up_click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, (ClickHandler) down_click_handler);
  window_single_click_subscribe(BUTTON_ID_SELECT, (ClickHandler) select_click_handler);
}

static void in_received_handler(DictionaryIterator *iter, void *context) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "App Message Received!");
}

static void in_dropped_handler(AppMessageResult reason, void *context) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "App Message Dropped!");
}

static void out_failed_handler(DictionaryIterator *failed, AppMessageResult reason, void *context) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "App Message Failed to Send!");
}

static void app_message_init(void) {
  // Register message handlers
  app_message_register_inbox_received(in_received_handler);
  app_message_register_inbox_dropped(in_dropped_handler);
  app_message_register_outbox_failed(out_failed_handler);
  // Init buffers
  app_message_open(64, 64);
}

static void window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  text_layer = text_layer_create((GRect) { .origin = { 0, bounds.size.h / 2 - 14 }, .size = { bounds.size.w - ACTION_BAR_WIDTH, 28 } });
  text_layer_set_text(text_layer, "00:00:00");
  text_layer_set_font(text_layer, fonts_get_system_font(FONT_KEY_DROID_SERIF_28_BOLD));
  text_layer_set_text_alignment(text_layer, GTextAlignmentCenter);
  layer_add_child(window_layer, text_layer_get_layer(text_layer));

  // Initialize the action bar:
  action_bar = action_bar_layer_create();
  // Associate the action bar with the window:
  action_bar_layer_add_to_window(action_bar, window);
  // Set the click config provider:
  action_bar_layer_set_click_config_provider(action_bar, click_config_provider);
  nextIcon = gbitmap_create_with_resource(RESOURCE_ID_NEXT_ICON);
  prevIcon = gbitmap_create_with_resource(RESOURCE_ID_PREV_ICON);
  timerIcon = gbitmap_create_with_resource(RESOURCE_ID_TIMER_ICON);
  action_bar_layer_set_icon(action_bar, BUTTON_ID_UP, nextIcon);
  action_bar_layer_set_icon(action_bar, BUTTON_ID_SELECT, timerIcon);
  action_bar_layer_set_icon(action_bar, BUTTON_ID_DOWN, prevIcon);
}

static void window_unload(Window *window) {
  stop_timer();
  text_layer_destroy(text_layer);
  action_bar_layer_destroy(action_bar);
}

static void init(void) {
  window = window_create();
  app_message_init();
  window_set_click_config_provider(window, click_config_provider);
  window_set_window_handlers(window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload,
  });
  const bool animated = true;
  window_stack_push(window, animated);
}

static void deinit(void) {
  window_destroy(window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}
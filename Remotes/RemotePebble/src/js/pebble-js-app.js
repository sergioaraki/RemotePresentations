var base_url = "http://192.168.1.103:8080";

Pebble.addEventListener("ready",
    function(e) {
        console.log("connect!" + e.ready);
        console.log(e.type);
    }
);

Pebble.addEventListener("appmessage",
                        function(e) {
                          if (e.payload.dir == 0) {
                            sendNext();
                          }
                          else {
                          	sendPrev();
                          }
                        });

function sendPrev() {
  var response;
  var req = new XMLHttpRequest();
  req.open('GET', base_url+"/prev.html", true);
  req.onload = function(e) {
    if (req.readyState == 4) {
      if(req.status == 200) {
        console.log('SendPrev');
      } 
    }
  }
  req.send(null);
}

function sendNext() {
  var response;
  var req = new XMLHttpRequest();
  req.open('GET', base_url+"/next.html", true);
  req.onload = function(e) {
    if (req.readyState == 4) {
      if(req.status == 200) {
        console.log('SendNext');
      } 
    }
  }
  req.send(null);
}
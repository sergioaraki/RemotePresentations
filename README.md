RemotePresentations
===================

Controls HTML5 presentation with mobile apps

You will need node.js (http://nodejs.org/) running in the computer with the HTML5 presentation.

Create a folder where you will copy the content of Server folder of this repo.

In that folder you need to run this command:

```
npm install
```

and then:

```
node server.js
```

Access in the computer to: localhost:8080/presentations/presentation1

For PebbleRemote, you can install the client from this url: http://www.arakisergio.com.ar/Presentation.pbw

Your phone and computer need to be in the same network, or your phone at least needs to reach your computer ip address.

In your phone, in the Official Pebble App run the configuration screen of Presentation, set the ip address of the computer running the node server.

Open Presentation app in your Pebble, and you can move to previous or next slide of the presentation, and you can start a timer to knows how long is your presentation running.

In the node server folder, you will need to modify presentations to match your needs, presentations are made with Reveal.js (https://github.com/hakimel/reveal.js/)

Just take care you don´t forget the last part of the html:

```js
<script src="http://localhost:8082/socket.io/socket.io.js"></script>
<script>
    var socket = io.connect('http://localhost:8082');
    socket.emit('reveal');
    socket.on('reveal_prev', function (data) {
        Reveal.prev();
    });
    socket.on('reveal_next', function (data) {
        Reveal.next();
	  });
</script>
```

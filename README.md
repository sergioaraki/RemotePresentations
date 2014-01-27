RemotePresentations
===================

Controls HTML5 presentations with mobile apps

Requirements
---
Your mobile phone and computer needs to be on the same network. Your mobile phone needs to reach your computer IP address.
Presentations created with Reveal.js (https://github.com/hakimel/reveal.js/)

Server side
---
You will need node.js (http://nodejs.org/) running on the computer with the HTML5 presentation.

Create a folder, and copy the content of the Server folder.

Change to that folder and run this command:

```
npm install
```

and then:

```
node server.js
```

Access in the computer to: localhost:8080/presentations/presentation1

Your presentations must reside in the node server folder.

Don't forget to add this last script to the end of the presentation's html:

```
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

Client side
---
You need to run RemotePebble on your mobile.

You can install RemotePebble client from this url: http://www.arakisergio.com.ar/Presentation.pbw

In your mobile, run Presentation configuration screen, from the Official Pebble App. Then, set the IP address of the computer running the node server.

Run Presentation app in your Pebble, and you will be able to move to the presentation's next or previous slide. You can also start a timer to know how long your presentation is taking.

You can explore the source code of RemotePebble in the folder Remotes/RemotePebble of this repo.

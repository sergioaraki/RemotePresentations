var io = require('socket.io').listen(8082);
var reveal_socket_id;
var control_socket_id;

io.configure( function() {
io.set('close timeout', 60*60*24); // 24h time out
});

io.sockets.on('connection', function (socket) {
  
  socket.emit('ready', 'Server ready');

  socket.on('reveal', function (data) {
    reveal_socket_id = socket.id;
    console.log('reveal connected');
  });

  socket.on('control', function (data) {
    control_socket_id = socket.id;
    console.log('control connected');
  });
  
  socket.on('prev', function (data) {
    if(reveal_socket_id != null){
		  io.sockets.socket(reveal_socket_id).emit('reveal_prev');	
		  console.log('reveal prev');
    }else{
		  console.error('reveal is not connected yet');
    }
  });

  socket.on('next', function (data) {
    if(reveal_socket_id != null){
		  io.sockets.socket(reveal_socket_id).emit('reveal_next');	
		  console.log('reveal next');
    }else{
		  console.error('reveal is not connected yet');
    }
  });
});
var client = require('socket.io-client');
var socket_client = client.connect("http://localhost:8082");
socket_client.on('connect', function(){
		    socket_client.emit('control');
		});
var connect = require('connect');
var s = connect.createServer(connect.static(__dirname));
s.use(function(req, res){
	if (req.url == '/next.html') {
		socket_client.emit('next');
		res.end('Next');
	}
	else if (req.url == '/prev.html') {
		socket_client.emit('prev');
		res.end('Next');
	}
  });
s.listen(8080);
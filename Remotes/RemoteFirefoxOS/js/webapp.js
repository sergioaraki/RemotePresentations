(function () {

    var baseUrl = "http://10.255.110.148:8080"

    var clsStopwatch = function() {
        // Private vars
        var startAt = 0;    // Time of last start / resume. (0 if not running)
        var lapTime = 0;    // Time on the clock when last stopped in milliseconds
 
        var now = function() {
                return (new Date()).getTime(); 
            }; 
 
        // Public methods
        // Start or resume
        this.start = function() {
                startAt = startAt ? startAt : now();
            };
 
        // Stop or pause
        this.stop = function() {
                // If running, update elapsed time otherwise keep it
                lapTime = startAt ? lapTime + now() - startAt : lapTime;
                startAt = 0; // Paused
            };
 
        // Reset
        this.reset = function() {
                lapTime = startAt = 0;
            };
 
        // Duration
        this.time = function() {
                return lapTime + (startAt ? now() - startAt : 0); 
            };
    };
 
    var x = new clsStopwatch();
    var timer = document.querySelector("#lTimer");
    var clocktimer;

    function pad(num, size) {
        var s = "0000" + num;
        return s.substr(s.length - size);
    }
     
    function formatTime(time) {
        var h = m = s = 0;
        var newTime = '';
     
        h = Math.floor( time / (60 * 60 * 1000) );
        time = time % (60 * 60 * 1000);
        m = Math.floor( time / (60 * 1000) );
        time = time % (60 * 1000);
        s = Math.floor( time / 1000 );
     
        newTime = pad(h, 2) + ':' + pad(m, 2) + ':' + pad(s, 2);
        return newTime;
    }

    var prev = document.querySelector("#prev");
    if (prev) {
        prev.onclick = function () {
            var response;
            var req = new XMLHttpRequest();
            req.open('GET', baseUrl+"/prev.html", true);
            req.onload = function(e) {
                if (req.readyState == 4) {
                  if(req.status == 200) {
                    console.log('SendPrev');
                  } 
                }
            }
            req.send(null);
        }
    }

    var next = document.querySelector("#next");
    if (next) {
        next.onclick = function () {
            var response;
            var req = new XMLHttpRequest();
            req.open('GET', baseUrl+"/next.html", true);
            req.onload = function(e) {
                if (req.readyState == 4) {
                  if(req.status == 200) {
                    console.log('SendPrev');
                  } 
                }
            }
            req.send(null);
        }
    }

    var start = document.querySelector("#bStart");
    if (start) {
        start.onclick = function () {
            var func = function update() {
                timer.innerHTML = formatTime(x.time());
            };
            clocktimer = setInterval(func, 1000);
            x.start();
        }
    }

    var stop = document.querySelector("#bStop");
    if (stop) {
        stop.onclick = function () {
            x.stop();
            clearInterval(clocktimer);
        }
    }
})();
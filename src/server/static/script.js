player_classes = ['speler_beige', 'speler_blue', 'speler_green', 'speler_yellow', 'speler_pink'];
current_time = 0;
ended = false;

function timelog(s) {
	var now = (new Date()).getTime();
	var diff = now - current_time;
	//console.log("[" + diff.toString() + "] " + s);
	current_time = now;
}

function endgame() {
	if (!ended) {
		$("#game_ended").css("visibility", "visible");
		$("#game_ended").animate({opacity: 1}, 1000);
		ended = true;
	}
}

function startgame() {
	if (ended) {
		ended = false;
		$("#game_ended").animate({opacity: 0}, 1000, "swing", 
			function() { $("#game_ended").css("visibility", "hidden"); });
	}
}

String.prototype.hashCode = function() {
	var hash = 0;
	if (this.length == 0) return hash;
	for (i = 0; i < this.length; i++) {
		char = this.charCodeAt(i);
		hash = ((hash<<5)-hash)+char;
		hash = hash & hash; // Convert to 32bit integer
	}
	return hash;
}

function player_class(naam) {
	naam = naam.trim();
	var hash = naam.hashCode();
	var i = hash % player_classes.length;
	return player_classes[i];
}

function rumble() {
	var timeout;
	var g = $('#grid_outer');
	clearTimeout(timeout);
	g.trigger('startRumble');
	timeout = setTimeout(function(){g.trigger('stopRumble');}, 200);
}

function get(x,y,table) {
	var t = table.children()[0].children;
	var realy = t.length - y - 1;
	return $(t[realy].children[x]);
}

function parse_entity(e) {
	var divs = [document.createElement("div")];
	divs[0].classList.add(e.tagName.toLowerCase());
	divs[0].classList.add("entity");
	
	// Special entities
	switch (e.tagName) {
		case "SPELER":
			var naam = e.getElementsByTagName("NAAM")[0].textContent;
			divs[0].setAttribute("title", naam);
			divs[0].classList.add(player_class(naam));
			break;
		case "KNOP":
			divs[0].setAttribute("title", e.getAttribute("id"));
			break;
		case "POORT":
			if (e.getAttribute("open") != undefined && e.getAttribute("open") == "1") {
				//console.log("open!");
				divs[0].setAttribute("hidden", "hidden");
			}
		case "MONSTER":
			divs[0].setAttribute("title", e.getElementsByTagName("ID")[0].textContent);
			break;
		case "WATER":
			// Contained!
			if (e.getElementsByTagName("CONTAINED").length > 0 && e.getElementsByTagName("CONTAINED")[0].children[0] != undefined) {
				divs.push(parse_entity(e.getElementsByTagName("CONTAINED")[0].children[0])[0]);
			}
			break;
	}
	
	if (e.tagName == "SPELER" || e.tagName == "MONSTER") {
		var name = divs[0].getAttribute("title").trim();
		if ($("#name_"+name).length == 0) {
			var name_radio = $('<input type="radio" name="names" id="name_'+name+'"value="'+name+'" /><label for="name_'+name+'"><div class="name_text">'+name+'</div></label>');
			if (e.tagName == "SPELER") {
				name_radio.prepend($('<div class="name_pic"/>').addClass(player_class(name)));
			} else {
				name_radio.prepend($('<div class="name_pic"/>').addClass("monster"));
			}
			$("#nameform").append(name_radio);
		}
	}
	
	return divs;
}

function place(e, table) {
	var x = parseInt(e.getAttribute("x"));
	var y = parseInt(e.getAttribute("y"));
	var cell = get(x,y,table);
	var divs = parse_entity(e);
	for (var i=0; i<divs.length; i++) {
		cell.prepend(divs[i]);
	}
}

function refresh_grid(el) {
	timelog("start refresh");
	var width = parseInt(el.getElementsByTagName("BREEDTE")[0].textContent)
	var length = parseInt(el.getElementsByTagName("LENGTE")[0].textContent)
	
	// Create table
	var table = $("<table id='grid'/>");
	for (i=0; i<length; i++) {
		var row = $("<tr/>");
		for (j=0; j<width; j++) {
			row.append($("<td/>"));
		}
		table.append(row);
	}
	
	
	// Put elements in place
	for (var i=0; i<el.children.length; i++) {
		var e = el.children[i];
		if (e.tagName != "BREEDTE" && e.tagName != "LENGTE" && e.tagName != "NAAM") {
			place(e, table);
		}
	}
	
	$("#grid_inner").empty();
	$("#grid_inner").append(table);
	
	timelog("end refresh");
}



// ----- Network, XML stuff and more -----

var dom_parser = new DOMParser();

function on_socket_message(event) {
	timelog("start onmessage ---------");
	////console.log(event);
	timelog("before parsing");
	var doc = dom_parser.parseFromString(event.data, "application/xml");
	timelog("after parsing");
	var root = doc.children[0];
	var veld_els = root.getElementsByTagName("VELD");
	if (veld_els.length > 0) {
		refresh_grid(veld_els[0]);
	}
	
	var logs = root.getElementsByTagName("LOG");
	if (logs.length > 0) {
		var content = logs[0].textContent;
		if (content != "") {
			$("#log").append(content);
			$("#log").append($('<br/>'));
			$('#log').scrollTop($('#log')[0].scrollHeight);
		}
	}
	
	var statuses = root.getElementsByTagName("STATUS");
	if (statuses.length > 0) {
		//console.log(status);
		var statusstr = statuses[0].textContent;
		if (statusstr != "OK") {
			rumble();
		}
	}
	
	//console.log(root);
	var ended_els = root.getElementsByTagName("ENDED");
	if (ended_els.length > 0) {
		endgame();
	} else {
		startgame();
	}
	timelog("end onmessage -----------");
}

function do_action(dir, e) {
	if (!ended) {
		var name;
		var total = "";
		if (e.ctrlKey) {
			name = "AANVAL";
		} else {
			name = "BEWEGING";
		}
		total += "<" + name + ">\n";
		total += "<ID>" + $("input[type='radio'][name='names']:checked").val() + "</ID>\n";
		total += "<RICHTING>" + dir + "</RICHTING>\n";
		total += "</" + name + ">";
		
		send("DOOO", total);
	}
}

function send(mode, data) {
	////console.log(mode + ":" + data);
	socket.send(mode + ":" + data);
}

$( document ).ready(function() {
    //console.log("ready!");
	
	// Init all the elements that need to be able to rumble
	$('#grid_outer').jrumble();
	
	// Loop audio
	var music = $('#bgmusic')[0];
	music.play();
	music.addEventListener('ended', function() {
		music.src = music.src;  // very ugly chrome hack, doesn't work otherwise
		$('#bgmusic')[0].play();
		////console.log("loop");
	}, false);
	
	// Keyboard
	$(document).keydown(function(e) {
		timelog("pressed key");
		switch(e.which) {
			case 37: // left
				do_action("LINKS", e);
				break;

			case 38: // up
				do_action("OMHOOG", e);
				break;

			case 39: // right
				do_action("RECHTS", e);
				break;

			case 40: // down
				do_action("OMLAAG", e);
				break;

			default: return; // exit this handler for other keys
		}
		e.preventDefault(); // prevent the default action (scroll / move caret)
	});
	
	// Set up the websockets
	socket = new WebSocket("ws://"+window.location.hostname+":8081");
	
	socket.onmessage = on_socket_message;
	
	socket.onconnect = function (event) {
		// get board
		send("SHOW", "");
		//console.log("socket ready");
	}
	
	socket.onopen = socket.onconnect;
	
	if (socket.readyState == socket.OPEN) {
		socket.onconnect();
	}
	
	// Set restart button
	$("#restart_button").on('click', function() {
		send("RSET","");  // reset the game
	});
});

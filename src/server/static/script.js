player_classes = ['speler_beige', 'speler_blue', 'speler_green', 'speler_yellow', 'speler_pink'];

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

function get(x,y) {
	var t = $('#grid').children()[0].children;
	var realy = t.length - y - 1;
	return $(t[realy].children[x]);
}

function parse_entity(e) {
	var div = $('<div class="entity"/>').addClass(e.getName().toLowerCase());
	
	// Special entities
	switch (e.getName()) {
		case "SPELER":
			var naam = e.getChildElement("NAAM").getContents().toString()
			div.attr("title", naam);
			div.addClass(player_class(naam));
			break;
		case "KNOP":
			div.attr("title", e.getAttribute("id").getValue());
			break;
		case "POORT":
			if (e.getAttribute("open") != undefined && e.getAttribute("open").getValue() == "1") {
				console.log("open!");
				div.attr("hidden", "hidden");
			}
		case "MONSTER":
			div.attr("title", e.getChildElement("ID").getContents().toString());
			break;
		case "WATER":
			// Contained!
			div = [div];
			if (e.getChildElement("CONTAINED") != undefined && e.getChildElement("CONTAINED").getChildElements()[0] != undefined) {
				div.push(parse_entity(e.getChildElement("CONTAINED").getChildElements()[0]));
			}
			div.reverse();
			break;
	}
	
	return div;
}

function place(e) {
	var x = parseInt(e.getAttribute("x").getValue());
	var y = parseInt(e.getAttribute("y").getValue());
	var cell = get(x,y);
	var div = parse_entity(e);
	cell.prepend(div);
}

function refresh_grid(el) {
	var width = parseInt(el.getChildElement("BREEDTE").getContents().toString());
	var length = parseInt(el.getChildElement("LENGTE").getContents().toString());
	
	// Create table
	var table = $("<table id='grid'/>");
	for (i=0; i<length; i++) {
		var row = $("<tr/>");
		for (j=0; j<width; j++) {
			row.append($("<td/>"));
		}
		table.append(row);
	}
	$("#grid_outer").empty();
	$("#grid_outer").append(table);
	
	// Put elements in place
	el.getChildElements().forEach(function(e) {
		if (e.getName() != "BREEDTE" && e.getName() != "LENGTE" && e.getName() != "NAAM") {
			place(e);
		}
	});
}

function ajax_callback(doc, params) {
	var root = doc.getRootElement();
	var veld_el = root.getChildElement("VELD");
	if (veld_el != undefined) {
		refresh_grid(veld_el);
	}
	
	var content = root.getChildElement("LOG").getContents().toString();
	if (content != "") {
		$("#log").append(content);
		$("#log").append($('<br/>'));
		$('#log').scrollTop($('#log')[0].scrollHeight);
	}
	
	var status = root.getChildElement("STATUS").getContents().toString();
	if (status != "OK") {
		console.log(status);
		rumble();
	}
}

function do_action(dir, e) {
	var ajax = new marknote.AJAX();
	
	var element;
	if (e.ctrlKey) {
		element = new marknote.Element("AANVAL");
	} else {
		element = new marknote.Element("BEWEGING");
	}
	
	var id = new marknote.Element("ID");
	id.setText($('#name').val());
	
	var richting = new marknote.Element("RICHTING");
	richting.setText(dir);
	
	element.addChildElement(id);
	element.addChildElement(richting);
	
	var urlParams = {
		mode: "do",
		action: element.toString(),
	};
	// optional callback parameters
	var callbackParams = {};
	// read the URL
	// (the callback handles the response)
	ajax.read(
		"ajax",
		urlParams, 
		ajax_callback,
		callbackParams,
		"POST"
	);
}

$( document ).ready(function() {
    console.log( "ready!" );
	
	// Init all the elements that need to be able to rumble
	$('#grid_outer').jrumble();
	
	// Keyboard
	$(document).keydown(function(e) {
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
	
	// First Ajax call
	var ajax = new marknote.AJAX();
	// optional request parameters
	var urlParams = {
		mode: "show",
	};
	// optional callback parameters
	var callbackParams = {};
	
	// read the URL
	// (the callback handles the response)
	ajax.read(
		"ajax",
		urlParams, 
		ajax_callback,
		callbackParams,
		"POST"
	);
	
});
function rumble() {
	var timeout;
	g = $('#grid_outer');
	clearTimeout(timeout);
	g.trigger('startRumble');
	timeout = setTimeout(function(){g.trigger('stopRumble');}, 200);
}

$( document ).ready(function() {
    console.log( "ready!" );
	
	// Init all the elements that need to be able to rumble
	$('#grid_outer').jrumble();

	$('#controls').click(function(){
		rumble();
	});

});
var catchObj;
var bMouseDown = false;

function init(){
	var height = window.innerHeight;
	var width = window.innerWidth;
	$("div#container")
		.css("width",width)
		.css("height",height);


	$("<div>")
		.addClass("div-sara")
		.css("top",Math.random() * (height - 400))
		.css("left",Math.random() * (width - 400))
		.appendTo($("#container"));

	for (var i = 0; i < 100; i++){
		var mame = $("<div>")
			.addClass("div-mame")
			.css("top",Math.random() * (height - 20))
			.css("left",Math.random() * (width - 20));
		if (Math.random() > 0.5){
			mame.addClass("mame1");
		}
		else{
			mame.addClass("mame2");
		}
		mame.rotate(360 * Math.random() + "deg");
		mame.appendTo($("#container"));
	}

	$("div.div-mame").mousedown(function(){
		bMouseDown = true;
		catchObj = $(this);
	});

	$("div#container").mousemove(function(e){
		if (bMouseDown){
			//console.log(catchObj);
			catchObj
			.css("top",e.clientY - 20)
			.css("left",e.clientX - 20);
		}
	});


	$("div#container").mouseup(function(){
		bMouseDown = false;
	});
}
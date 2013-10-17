var catchObj;
var bMouseDown = false;
var z = 1;

function init(){
	var height = window.innerHeight;
	var width = window.innerWidth;
	var rand = Math.floor(Math.random() * 3);
	$("div#container")
		.css("width",width)
		.css("height",height);
	$("div#container").css("background-image","url('./images/bg_00"+rand+".jpg')");


	$("<div>")
		.addClass("div-sara")
		.css("top",Math.random() * (height - 400))
		.css("left",Math.random() * (width - 400))
		.appendTo($("#container"));

	for (var i = 0; i < 40; i++){
		var mame = $("<div>")
			.addClass("div-mame")
			.css("top",Math.random() * (height - 20))
			.css("left",Math.random() * (width - 20));
		var mamerand = 2;//Math.floor(Math.random() * 2.005);
		mame.addClass("mame"+(mamerand+1));
		
		mame.rotate(360 * Math.random() + "deg");
		mame.appendTo($("#container"));
	}

	$("<div>")
		.addClass("hashi")
		.attr("id","hashi")
		.appendTo($("#container"));

	//add event handler
	$("div.div-mame").mousedown(function(){
		bMouseDown = true;
		catchObj = $(this);
		catchObj.css("z-index",z++);
		catchObj.scale(1.2);
	});

	$("div#container").mousemove(function(e){
		if (bMouseDown){
			//console.log(catchObj);
			catchObj
			.css("top",e.clientY - 20)
			.css("left",e.clientX - 20);
		}
		$("#hashi")
			.css("top",e.clientY - 196)
			.css("left",e.clientX + 2);
	});


	$("div#container").mouseup(function(){
		bMouseDown = false;
		catchObj.scale(1.0);
	});
}
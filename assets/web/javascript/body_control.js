function body_center()
{
	document.getElementById("content").style.left = "10%";
}

function body_left()
{
	document.getElementById("content").style.left = "0%";
}

function body_right()
{
	document.getElementById("content").style.left = "20%";
}

function changeBody(x)
{
	AJAX_GET(x, function(y)
	{
		document.getElementById("content").innerHTML = y;
	});
}
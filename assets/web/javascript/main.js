//The bootloader
window.onload = function()
{
	changeBody("/file/html?loc=assets/web/html/home.mdhtml");
	boot_navigator();
}

function changeReason(x)
{
	AJAX_GET("/file/html?loc=assets/web/html/why/" + x + ".dat", function(y)
	{
		document.getElementById("target").innerHTML = y;
	});
}

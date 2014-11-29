//The bootloader
window.onload = function()
{
	changeBody("/file/html?loc=assets/web/html/home.mdhtml");
	boot_navigator();
	closeAppsPage();
}

function changeReason(x)
{
	AJAX_GET("/file/html?loc=assets/web/html/why/" + x + ".dat", function(y)
	{
		document.getElementById("target").innerHTML = y;
	});
}

var ImageLoaderBoot = setInterval(function()
{
	clearInterval(ImageLoaderBoot);
	document.getElementById("topnav_img").src = "/file/png?loc=assets/web/png/UberScout.png";
}, 1000);
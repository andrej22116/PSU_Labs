// Button for enable/disable lamp
var buttonPower;
// Form with range control
var rangePowerForm;
// Range control 
var rangePower;
// Text block for output value from form.range
var rangePowerTextOutput;

var mainBlock;
var overhead;

var request;

function onButtonPowerClick() {
	if ( buttonPower.getAttribute("value") == "on" ) {
		buttonPower.innerHTML = "Включить";
		buttonPower.setAttribute("value", "off");
		rangePowerForm.style.display = "none";
	}
	else {
		buttonPower.innerHTML = "Выключить";
		buttonPower.setAttribute("value", "on");
		rangePowerForm.style.display = "flex";
		rangePower.value = "100";
		rangePowerTextOutput.innerHTML = "100%";
	}
	
	request = sendAjaxGetRequest(
		"powerControl.php", 
		"power=" + buttonPower.getAttribute("value"),
		function() {
			if (request.readyState == 4) {
				if (request.status != 200) {
					alert("Не удалось установить значение power!");
				}
			}
		}
	);
}

function onButtonBlickClick() {
	overhead.style.visibility = "visible";
	mainBlock.style.filter = "blur(4px)";
	
	request = sendAjaxGetRequest(
		"powerControl.php", 
		"blick=1",
		function() {
			if (request.readyState == 4) {
				if (request.status != 200) {
					alert("Не удалось установить значение power!");
				}
				
				overhead.style.visibility = "hidden";
				mainBlock.style.filter = "none";
			}
		}
	);
}

function onPowerInput() {	
	rangePowerTextOutput.innerHTML = rangePower.value + "%";
	
	request = sendAjaxGetRequest(
		"powerControl.php", 
		"pulse-width=" + rangePower.value,
		function() {
			if (request.readyState == 4) {
				if (request.status != 200) {
					alert("Не удалось установить значение pulse-width!");
				}
			}
		}
	);
}

function sendAjaxGetRequest(file, params, callbackFunction)
{
	var url = file + "?" + params;
	var request = initRequest();
	request.open("GET", url, true);
	request.onreadystatechange = callbackFunction;
	request.send();
	return request;
}

function initRequest() {
    if (window.XMLHttpRequest) {
        return new XMLHttpRequest();
    } else if (window.ActiveXObject) {
        return new ActiveXObject("Microsoft.XMLHTTP");
    }
}

function main()
{
	buttonPower = document.getElementById("button-power");
	rangePower = document.getElementById("power-range");
	rangePowerForm = rangePower.parentElement;
	rangePowerTextOutput = document.getElementById("power-output");
	overhead = document.getElementById("overhead");
	mainBlock = document.getElementById("main");
	
	rangePowerForm.style.display = "none";
	overhead.style.visibility = "hidden";
}

main();
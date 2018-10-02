function main() {
    var inputs = document.getElementsByTagName("input");
    for (var i = 0; i < inputs.length; i++) {
        if (inputs[i].dataset.hint == undefined) continue;

        var newElement = document.createElement('label');
        newElement.innerHTML = '<b>?</b>';
        newElement.setAttribute('title', inputs[i].dataset.hint);
        newElement.style.borderWidth = '1';
        newElement.style.borderColor = 'green';
        newElement.style.borderStyle = 'solid';
        newElement.style.fontSize = '14px';
        newElement.style.padding = "0 5px 0 5px";

        if (inputs[i].nextSibling == undefined) {
            inputs[i].parentNode.appendChild(newElement);
        }
        else {
            inputs[i].parentNode.insertBefore(newElement, inputs[i].nextSibling);
        }        
    }
}

main();
function insertAfter(newNode, afterElement) {
    if (afterElement.nextElementSibling == null) {
        afterElement.parentElement.appendChild(newNode);
    }
    else {
        afterElement.parentElement.insertBefore(newNode, afterElement.nextElementSibling);
    }
}

function setErrorMessage(input, message) {
    var errorElement = document.createElement('label');
    errorElement.style.color = 'red';
    errorElement.style.border = '1px solid red';
    errorElement.style.padding = "2px 10px 2px 10px";
    errorElement.style.margin = "0 10px 0 0";
    errorElement.innerHTML = message;
    errorElement.setAttribute('error-message', '!');
    
    insertAfter(errorElement, input);

    return false;
}

function removeOldErrorMessage(input) {
    if(input.nextElementSibling != null 
        && input.nextElementSibling.getAttribute('error-message') == '!') {
        input.parentElement.removeChild(input.nextElementSibling);
    }
}

function validateIntegerInput(input) {
    removeOldErrorMessage(input);

    if (input.value == '' || input.value.split(/[^(-?\d*)]/).length > 1) { 
        return setErrorMessage(input, "Введите число!"); 
    }

    if (input.getAttribute('minrange') != null && +input.value < +input.getAttribute('minrange')) {
        return setErrorMessage(input, "Число должно быть больше или равно " + input.getAttribute('minrange') + "!");
    }
    if (input.getAttribute('maxrange') != null && +input.value > +input.getAttribute('maxrange')) {
        return setErrorMessage(input, "Число должно быть меньше или равно " + input.getAttribute('maxrange') + "!");
    }

    return true;
}

function validate(form)
{
    var childElemets = form.getElementsByTagName('input');
    var dataIsAcceptable = true;

    for (var i = 0; i < childElemets.length; i++) {
        if (childElemets[i].getAttribute('extype') == 'integer') {
            if (!validateIntegerInput(childElemets[i])) {
                dataIsAcceptable = false;
            }
        }
    }

    if (!dataIsAcceptable) {
        event.preventDefault(); 
    }
}
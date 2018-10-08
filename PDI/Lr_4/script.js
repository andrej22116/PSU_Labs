function payRespect()
{
    alert("Respect!");
}

function task_1(a, b, c)
{
    if (a > b && a > c) return a;
    else if ( b > a && b > c) return b;
    else return c;
}

function task_2(a, b)
{
    var multiplyAB = a * b;
    var result = 0;

    if (multiplyAB > 0.5 && multiplyAB < 10) {
        result = Math.exp(Math.abs(a) - Math.abs(b));
    }
    else if (multiplyAB > 0.1 && multiplyAB < 0.5) {
        result = Math.sqrt(Math.abs(a + b));
    }
    else {
        result = 2 * b * b;
    }

    return result;
}

function task_3(array)
{
    return array.sort ((a, b) => {

        var delta_a = Math.abs(a - Math.floor(a));
        var delta_b = Math.abs(b - Math.floor(b));

        return delta_a > delta_b ? 1 : -1;
    });
}

function task_4(str)
{
    var res = "";
    str.split(/[\.,!\?:-]+/).forEach(function (substring) {
        res += substring;
    });
    return res;
}

function task_5(array) {
    if (array.length == 0) return;

    var min_pos = 0;
    var min = array[min_pos];

    var max_pos = 0;
    var max = array[max_pos];

    for (var i = 1; i < array.length; i++) {
        if (array[i] < min) {
            min = array[i];
            min_pos = i;
        }
        else if (array[i] > max) {
            max = array[i];
            max_pos = i;
        }
    }

    array.splice(Math.min(min_pos, max_pos) + 1, Math.abs(min_pos - max_pos) - 1);

    return array;
}

function task_6(text, word) {
    return text.split(word).length - 1;
}

function task_7(text) {
	var res = ""
	text.split(" ").forEach( word => {		
		word = word.split("").reverse().join("");
		
		if (res.length > 0) {
			res += " ";
		}
		res += word;
	});
	return res;
}

function task_8(str)
{
    var res = [];
    str.split(/[\.,!\?:-\s]+/).sort(function (str_1, str_2) {
        return str_1.length - str_2.length;
    }).forEach(function (substring) {
        if (substring.length > 0) {
            res.push(substring);
        }
    });
    return res;
}

function task_9(str, from, to) {
    var res = "";
    str.split(from).forEach(function (substring) {
        if (res.length > 0) {
            res += to + substring;
        }
        else {
            res += substring;
        }
    });
    return res;
}

function pluck(array, field) {
    var result = [];
    array.forEach(function (character) {
        result.push(character[field]);
    });
    return result;
}

function test_pluck()
{
    var characters = [

        { 'name': 'barney', 'age': 36 },
        
        { 'name': 'fred', 'age': 40 }
        
        ];
    return pluck(characters, 'name');
}

function map(fn, array)
{
    var res = [];
    array.forEach(function(element) {
        res.push(fn(element));
    });
    return res;
}

function test_map()
{
    return map(function(element) {
        return element * element;
    }, [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]);
}

function filter(array, fun) {
    var res = [];
    array.forEach(function(element) {
        if (fun(element) === true) {
            res.push(element);
        }
    });
    return res;
}

function test_filter()
{
    var input = [1, 2, 3, 4, 5, 6]; 
    function isEven(x) { return x % 2 == 0; }
    return filter(input, isEven);
}
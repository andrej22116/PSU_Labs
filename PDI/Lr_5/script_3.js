var nextSymbol = 'x'
var winStatus = false;

function checkWin() {
    var matrix = [
        [c0.innerHTML, c1.innerHTML, c2.innerHTML],
        [c3.innerHTML, c4.innerHTML, c5.innerHTML],
        [c6.innerHTML, c7.innerHTML, c8.innerHTML]
    ];
}

function update(cell) {
    if (cell.innerHTML == '') {
        cell.innerHTML = nextSymbol;
        cell.className = 'closedCell';

        if (nextSymbol == 'x') {
            nextSymbol = 'o';
            info.innerHTML = 'Ходят нолики!';
        } 
        else {
            nextSymbol = 'x';
            info.innerHTML = 'Ходят крестики!';
        }
    }
}

function newGame() {
    var cells = field.getElementsByTagName('td');
    for (var i = 0; i < cells.length; i++) {
        cells[i].innerHTML = '';
        cells[i].className = 'baseCell';
    }

    nextSymbol = 'x';
    info.innerHTML = 'Ходят крестики!';
}

function main()
{
    var cells = field.getElementsByTagName('td');
    for (var i = 0; i < cells.length; i++) {
        cells[i].setAttribute("onclick", "update(this)");
    }

    newGame();
}

main();
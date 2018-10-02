var nextSymbol = 'x'
var cellsClosed = 0;
var gameOver = false;

function colorizePlayers(whoWin) {
    var cells = field.getElementsByTagName('td');
    for (var i = 0; i < cells.length; i++) {
        if (cells[i].innerHTML == whoWin) {
            cells[i].className = 'winCell';
        } 
        else if (cells[i].innerHTML != '') {
            cells[i].className = 'looseCell';
        }
    }
}

function checkLines(matrix, player) {
    for (var i = 0; i < 3; i++) {
        var vertical = true;
        var horizontal = true;

        for (var j = 0; j < 3; j++) {
            vertical &= matrix[i][j] == player;
            horizontal &= matrix[j][i] == player;
        }

        if (vertical || horizontal) { return true; }
    }

    return false;
}

function checkDiagonal(matrix, player) {
    var tripple_left = true;
    var tripple_right = true;

    for (var i = 0; i < 3; i++) {
        tripple_left &= matrix[i][i] == player;
        tripple_right &= matrix[2 - i][i] == player;
    }

    return tripple_left || tripple_right;
}

function checkPlayerWin() {
    var matrix = [
        [c0.innerHTML, c1.innerHTML, c2.innerHTML],
        [c3.innerHTML, c4.innerHTML, c5.innerHTML],
        [c6.innerHTML, c7.innerHTML, c8.innerHTML]
    ];
    
    console.log(matrix);
    
    if (checkDiagonal(matrix, 'x') || checkLines(matrix, 'x')) {
        colorizePlayers('x');
        return 'Победили крестики!';
    }
    else if (checkDiagonal(matrix, 'o') || checkLines(matrix, 'o')) {
        colorizePlayers('o');
        return 'Победили нолики!';
    }

    return '';
}

function update(cell) {
    if (cell.innerHTML == '' && !gameOver) {
        cell.innerHTML = nextSymbol;
        cell.className = 'closedCell';
        cellsClosed++;

        var hwoWin = '';
        if (cellsClosed >= 5) {
            hwoWin = checkPlayerWin();
        }

        if (hwoWin != '') {
            gameOver = true;
            info.innerHTML = hwoWin;
            info.className = 'infoWin';
        }
        else if (cellsClosed == 9) {
            info.innerHTML = 'Ничья!';
        }
        else if (nextSymbol == 'x') {
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

    gameOver = false;
    cellsClosed = 0;
    nextSymbol = 'x';
    info.innerHTML = 'Ходят крестики!';
    info.className = 'infoBase'
}

function initialize() {
    var cells = field.getElementsByTagName('td');
    for (var i = 0; i < cells.length; i++) {
        cells[i].setAttribute("onclick", "update(this)");
    }
}

function main()
{
    initialize();
    newGame();
}

main();
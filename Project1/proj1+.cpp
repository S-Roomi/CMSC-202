void resetGame(){
    char playAgain = 'o';
    cout << "Would you like to play again? (y or n)" << endl;
    cin >> playAgain;
    while (playAgain != "y" or playAgain != "n"){
        cout << "Please type y or n" << endl;
        cin >> playAgain;
    }
    if (playAgain == "y"){
        resetGrid(gridX, gridY,grid);
    }else{
        foundBal = true;
    }
}
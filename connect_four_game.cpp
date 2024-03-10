#include <bits/stdc++.h>
using namespace std;

// Below is the implementation of Connect Four game.
// Follow up Question to be solved next- Algorithm to find the best colum to drop the coin.
class ConnectFour
{

private:
    int totalRows;
    int totalCols;
    // board configuration
    vector<vector<int>> board;
    //shows the top available spot for each column
    vector<int> topSpot;

public:
    ConnectFour(int totalRows, int totalCols)
    {
        this->totalRows = totalRows;
        this->totalCols = totalCols;
        board.resize(totalRows, vector<int>(totalCols, 0));
        //bottom spot available for each column
        topSpot.resize(totalCols, totalRows - 1);
    }

    int move(int col, int player)
    {
        // This function returns
        // -1 -> for invalid move
        // 1 -> player doesn't win after this move
        // int player -> if player wins after this move
        // Time Complexity - O(1)

        // If that column doesn't exist or that column is filled,
        // it's an invalid move.
        if((col < 0) || (col >= totalCols) || (topSpot[col] < 0))
        {
            cout << "Not a valid move\n";
            return -1;
        }
        else
        {
            board[topSpot[col]][col] = player;
            topSpot[col]--;
        }

        if(isWinner(col, player) != 0)
            return player;

        return 0;
    }

    bool isWinner(int col, int player)
    {
        // Time Complexity - O(1)

        //row num where player placed the ball
        int row = topSpot[col] + 1;

        //Checking vertically
        if(isInside(row, col, row+3, col) && (board[row][col] == player) && 
            (board[row+1][col] == player) && 
            (board[row+2][col] == player) && 
            (board[row+3][col] == player))
        return player;

        //Checking horizontally
        for(int j = col - 3; j <= col; j++)
        {
            if(isInside(row, j, row, j + 3) && 
                (board[row][j] == player) && 
                (board[row][j+1] == player) && 
                (board[row][j+2] == player) && 
                (board[row][j+3] == player))
            return player;
        }

        //Checking diagonally
        for(int i = row-3, j = col-3; (i <= row) & (j <= col); i++, j++)
        {
            if(isInside(i, j, i + 3, j + 3) && 
                (board[i][j] == player) && 
                (board[i+1][j+1] == player) && 
                (board[i+2][j+2] == player) && 
                (board[i+3][j+3] == player))
            return player;
        }

        //Checking anti-diagonally
        for(int i = row-3, j = col+3; (i <= row ) & (j >= col); i++, j--)
        {
            if(isInside(i, j, i + 3, j - 3) && 
                (board[i][j] == player) && 
                (board[i+1][j-1] == player) && 
                (board[i+2][j-2] == player) && 
                (board[i+3][j-3] == player))
            return player;
        }

        return 0;
    }

    bool isInside(int row1, int col1, int row2, int col2)
    {
        if((row1 < 0)|| (col1 < 0) || (row2 < 0) || (col2 < 0))
        return false;

        if((row1 >= totalRows)|| (col1 >= totalCols) || (row2 >= totalRows) || (col2  >= totalCols))
        return false;

        return true;
    }

    void display()
    {
        for(int i = 0; i < totalRows; i++)
        {
            for(int j = 0; j < totalCols; j++)
            cout << board[i][j] << " ";

            cout << "\n";
        }
    }
};

int main()
{
    int rows, cols;
    cout << "Enter rows and cols\n";
    cin >> rows >> cols;

    ConnectFour *connectFour = new ConnectFour(rows, cols);
    connectFour->display();

    int player = 1;
    while(1)
    {
        cout << "Player " << player << " enter column\n";

        int col;
        cin >> col;

        int output = connectFour->move(col, player);
        connectFour->display();

        if(output == 0)
        {
            player = (player == 1) ?  2 : 1;
        }

        else if(output == -1)
        {
            continue;
        }
        else
        {
            cout << "Player " << player << " is winner.\n";
            break;
        }
    }

    return 0;
}
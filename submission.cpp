#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <vector>
#include <map>
using namespace std;

struct par
{
  int board[10][4][3];
  vector< pair< pair<int,int> , pair<int,int> > > moves;
  int pID;
  int oID;
  int remaining_moves;
};

bool operator<(par a, par b)
{
  if(a.board!=b.board)
    return a.board<b.board;
    if(a.moves!=b.moves)
    return a.moves<b.moves;
    if(a.pID!=b.pID)
    return a.pID<b.pID;
    if(a.oID!=b.oID)
    return a.oID<b.oID;
    return a.remaining_moves<b.remaining_moves;
}

map< par, pair< pair< pair<int,int>, pair<int,int> > , pair<int,int> > > cache;

bool safe(int I,int J, int board[10][4][3],int pID,int oID)
{
  if(J>0)
  {
    if(board[I][J-1][0]==oID&&board[I][J-1][1]!=3)
    return 0;
  }
  if(J<3)
  {
    if(board[I][J+1][0]==oID&&board[I][J+1][1]!=3)
    return 0;
  }
  if(I>0)
  {
    if(board[I-1][J][0]==oID&&board[I-1][J][1]==1)
    return 0;
    if(board[I-1][J][0]==oID&&board[I-1][J][1]==2&&board[I-1][J][2]==1&&board[I+1][J][0]!=oID)
    return 0;
    if(J==1||J==2)
    {
      if(board[I-1][J+1][0]==oID&&board[I-1][J+1][1]==3&&board[I-1][J+1][2]==1&&board[I+1][J-1][0]!=oID)
      return 0;
      if(board[I-1][J-1][0]==oID&&board[I-1][J-1][1]==3&&board[I-1][J-1][2]==1&&board[I+1][J+1][0]!=oID)
      return 0;
    }
    if(J==0)
    {
      if(board[I-1][J+1][0]==oID&&board[I-1][J+1][1]==3&&board[I-1][J+1][2]==1&&board[I+1][J+1][0]!=oID)
      return 0;
    }
    if(J==3)
    {
      if(board[I-1][J-1][0]==oID&&board[I-1][J-1][1]==3&&board[I-1][J-1][2]==1&&board[I+1][J-1][0]!=oID)
      return 0;
    }
  }
  if(I<9)
  {
    if(board[I+1][J][0]==oID&&board[I+1][J][1]==1)
    return 0;
    if(board[I+1][J][0]==oID&&board[I+1][J][1]==2&&board[I+1][J][2]==0&&board[I-1][J][0]!=oID)
    return 0;
    if(J==1||J==2)
    {
      if(board[I+1][J+1][0]==oID&&board[I+1][J+1][1]==3&&board[I+1][J+1][2]==0&&board[I-1][J-1][0]!=oID)
      return 0;
      if(board[I+1][J-1][0]==oID&&board[I+1][J-1][1]==3&&board[I+1][J-1][2]==0&&board[I-1][J+1][0]!=oID)
      return 0;
    }
    if(J==0)
    {
      if(board[I+1][J+1][0]==oID&&board[I+1][J+1][1]==3&&board[I+1][J+1][2]==0&&board[I-1][J+1][0]!=oID)
      return 0;
    }
    if(J==3)
    {
      if(board[I+1][J-1][0]==oID&&board[I+1][J-1][1]==3&&board[I+1][J-1][2]==0&&board[I-1][J-1][0]!=oID)
      return 0;
    }
  }
  if(I>1)
  {
    if(board[I-2][J][0]==oID&&board[I-2][J][1]==2&&board[I-2][J][2]==1)
    return 0;
    if(board[I-2][J][0]==oID&&board[I-2][J][1]==3&&board[I-2][J][2]==1&&(J==1||J==2))
    return 0;
    if(J<2)
    {
      if(board[I-2][J+2][0]==oID&&board[I-2][J+2][1]==3&&board[I-2][J+2][2]==1)
      return 0;
    }
    else if(J>1)
    {
      if(board[I-2][J-2][0]==oID&&board[I-2][J-2][1]==3&&board[I-2][J-2][2]==1)
      return 0;
    }
  }
  if(I<8)
  {
    if(board[I+2][J][0]==oID&&board[I+2][J][1]==2&&board[I+2][J][2]==0)
    return 0;
    if(board[I+2][J][0]==oID&&board[I+2][J][1]==3&&board[I+2][J][2]==0&&(J==1||J==2))
    return 0;
    if(J<2)
    {
      if(board[I+2][J+2][0]==oID&&board[I+2][J+2][1]==3&&board[I+2][J+2][2]==0)
      return 0;
    }
    else if(J>1)
    {
      if(board[I+2][J-2][0]==oID&&board[I+2][J-2][1]==3&&board[I+2][J-2][2]==0)
      return 0;
    }
  }
  if(I==0)
  {
    if(J==0)
    {
      if(board[1][1][0]==oID&&board[1][1][1]==3)
      return 0;
    }
    else if(J==1)
    {
      if(board[1][0][0]==oID&&board[1][0][1]==3&&board[1][0][2]==0&&board[1][2][0]!=oID)
      return 0;
      if(board[1][2][0]==oID&&board[1][2][1]==3&&board[1][2][2]==0&&board[1][0][0]!=oID)
      return 0;
    }
    else if(J==2)
    {
      if(board[1][1][0]==oID&&board[1][1][1]==3&&board[1][1][2]==0&&board[1][3][0]!=oID)
      return 0;
      if(board[1][3][0]==oID&&board[1][3][1]==3&&board[1][3][2]==0&&board[1][1][0]!=oID)
      return 0;
    }
    else if(J==3)
    {
      if(board[1][2][0]==oID&&board[1][2][1]==3)
      return 0;
    }
  }
  else if(I==9)
  {
    if(J==0)
    {
      if(board[8][1][0]==oID&&board[8][1][1]==3)
      return 0;
    }
    else if(J==1)
    {
      if(board[8][0][0]==oID&&board[8][0][1]==3&&board[8][0][2]==1&&board[8][2][0]!=oID)
      return 0;
      if(board[8][2][0]==oID&&board[8][2][1]==3&&board[8][2][2]==1&&board[8][0][0]!=oID)
      return 0;
    }
    else if(J==2)
    {
      if(board[8][1][0]==oID&&board[8][1][1]==3&&board[8][1][2]==1&&board[8][3][0]!=oID)
      return 0;
      if(board[8][3][0]==oID&&board[8][3][1]==3&&board[8][3][2]==1&&board[8][1][0]!=oID)
      return 0;
    }
    else if(J==3)
    {
      if(board[8][2][0]==oID&&board[8][2][1]==3)
      return 0;
    }
  }
  return 1;
}

void calculate(vector< pair< pair<int,int> , pair<int,int> > > &moves,vector< pair< pair<int,int> , pair<int,int> > > &attack1,vector< pair< pair<int,int> , pair<int,int> > > &attack2, int board[10][4][3],int pID,int oID,int &pN,int &oN)
{
  pN=0;oN=0;
  for(int i=0;i<10;i++)
    {
      for(int j=0;j<4;j++)
      {
        if(board[i][j][0]==pID)
        {
          pN++;
          if(board[i][j][1]==1)
          {
            if(i>0)
            {
              if(board[i-1][j][0]==0)
              {
                moves.push_back({{i,j},{i-1,j}});
              }
              else if(board[i-1][j][0]==oID)
              {
                moves.push_back({{i,j},{i-1,j}});
                attack1.push_back({{i,j},{i-1,j}});
              }
            }
            if(i<9)
            {
              if(board[i+1][j][0]==0)
              {
                moves.push_back({{i,j},{i+1,j}});
              }
              else if(board[i+1][j][0]==oID)
              {
                moves.push_back({{i,j},{i+1,j}});
                attack1.push_back({{i,j},{i+1,j}});
              }
            }
            if(j>0)
            {
              if(board[i][j-1][0]==0)
              {
                moves.push_back({{i,j},{i,j-1}});
              }
              else if(board[i][j-1][0]==oID)
              {
                moves.push_back({{i,j},{i,j-1}});
                attack1.push_back({{i,j},{i,j-1}});
              }
            }
            if(j<3)
            {
              if(board[i][j+1][0]==0)
              {
                moves.push_back({{i,j},{i,j+1}});
              }
              else if(board[i][j+1][0]==oID)
              {
                moves.push_back({{i,j},{i,j+1}});
                attack1.push_back({{i,j},{i,j+1}});
              }
            }
          }
          else if(board[i][j][1]==2)
          {
            if(board[i][j][2]==0)					//upward
            {
              if(i>1)
              {
                if(board[i-2][j][0]==0)
                {
                  moves.push_back({{i,j},{i-2,j}});
                  if(board[i-1][j][0]==oID)
                  attack1.push_back({{i,j},{i-2,j}});
                }
                else if(board[i-2][j][0]==oID)
                {
                  moves.push_back({{i,j},{i-2,j}});
                  if(board[i-1][j][0]==oID)
                  attack2.push_back({{i,j},{i-2,j}});
                  else
                  attack1.push_back({{i,j},{i-2,j}});
                }
              }
              if(i==1)
              {
                moves.push_back({{i,j},{i,j}});
                if(board[i-1][j][0]==oID)
                {
                  attack1.push_back({{i,j},{i,j}});
                }
              }
              if(j>0)
              {
                if(board[i][j-1][0]==0)
                {
                  moves.push_back({{i,j},{i,j-1}});
                }
                else if(board[i][j-1][0]==oID)
                {
                  moves.push_back({{i,j},{i,j-1}});
                  attack1.push_back({{i,j},{i,j-1}});
                }
              }
              if(j<3)
              {
                if(board[i][j+1][0]==0)
                {
                  moves.push_back({{i,j},{i,j+1}});
                }
                else if(board[i][j+1][0]==oID)
                {
                  moves.push_back({{i,j},{i,j+1}});
                  attack1.push_back({{i,j},{i,j+1}});
                }
              }
            }
            else if(board[i][j][2]==1)				//downward
            {
              if(i<8)
              {
                if(board[i+2][j][0]==0)
                {
                  moves.push_back({{i,j},{i+2,j}});
                  if(board[i+1][j][0]==oID)
                  attack1.push_back({{i,j},{i+2,j}});
                }
                else if(board[i+2][j][0]==oID)
                {
                  moves.push_back({{i,j},{i+2,j}});
                  if(board[i+1][j][0]==oID)
                  attack2.push_back({{i,j},{i+2,j}});
                  else
                  attack1.push_back({{i,j},{i+2,j}});
                }
              }
              if(i==8)
              {
                moves.push_back({{i,j},{i,j}});
                if(board[i+1][j][0]==oID)
                {
                  attack1.push_back({{i,j},{i,j}});
                }
              }
              if(j>0)
              {
                if(board[i][j-1][0]==0)
                {
                  moves.push_back({{i,j},{i,j-1}});
                }
                else if(board[i][j-1][0]==oID)
                {
                  moves.push_back({{i,j},{i,j-1}});
                  attack1.push_back({{i,j},{i,j-1}});
                }
              }
              if(j<3)
              {
                if(board[i][j+1][0]==0)
                {
                  moves.push_back({{i,j},{i,j+1}});
                }
                else if(board[i][j+1][0]==oID)
                {
                  moves.push_back({{i,j},{i,j+1}});
                  attack1.push_back({{i,j},{i,j+1}});
                }
              }
            }
          }
          else if(board[i][j][1]==3)
          {
            if(board[i][j][2]==0)						//upward
            {
              if(j==0)
              {
                if(i>1)
                {
                  if(board[i-2][j+2][0]==0)
                  {
                    moves.push_back({{i,j},{i-2,j+2}});
                    if(board[i-1][j+1][0]==oID)
                    attack1.push_back({{i,j},{i-2,j+2}});
                  }
                  else if(board[i-2][j+2][0]==oID)
                  {
                    moves.push_back({{i,j},{i-2,j+2}});
                    if(board[i-1][j+1][0]==oID)
                    attack2.push_back({{i,j},{i-2,j+2}});
                    else
                    attack1.push_back({{i,j},{i-2,j+2}});
                  }
                }
                else if(i==1)
                {
                  if(board[i][j+2][0]==0)
                  {
                    moves.push_back({{i,j},{i,j+2}});
                    if(board[i-1][j+1][0]==oID)
                    attack1.push_back({{i,j},{i,j+2}});
                  }
                  else if(board[i][j+2][0]==oID)
                  {
                    moves.push_back({{i,j},{i,j+2}});
                    if(board[i-1][j+1][0]==oID)
                    attack2.push_back({{i,j},{i,j+2}});
                    else
                    attack1.push_back({{i,j},{i,j+2}});
                  }
                }
              }
              else if(j==1)
              {
                if(i>1)
                {
                  if(board[i-2][j+2][0]==0)
                  {
                    moves.push_back({{i,j},{i-2,j+2}});
                    if(board[i-1][j+1][0]==oID)
                    attack1.push_back({{i,j},{i-2,j+2}});
                  }
                  else if(board[i-2][j+2][0]==oID)
                  {
                    moves.push_back({{i,j},{i-2,j+2}});
                    if(board[i-1][j+1][0]==oID)
                    attack2.push_back({{i,j},{i-2,j+2}});
                    else
                    attack1.push_back({{i,j},{i-2,j+2}});
                  }
                  if(board[i-2][j][0]==0)
                  {
                    moves.push_back({{i,j},{i-2,j}});
                    if(board[i-1][j-1][0]==oID)
                    attack1.push_back({{i,j},{i-2,j}});
                  }
                  else if(board[i-2][j][0]==oID)
                  {
                    moves.push_back({{i,j},{i-2,j}});
                    if(board[i-1][j-1][0]==oID)
                    attack2.push_back({{i,j},{i-2,j}});
                    else
                    attack1.push_back({{i,j},{i-2,j}});
                  }
                }
                else if(i==1)
                {
                  if(board[i][j+2][0]==0)
                  {
                    moves.push_back({{i,j},{i,j+2}});
                    if(board[i-1][j+1][0]==oID)
                    attack1.push_back({{i,j},{i,j+2}});
                  }
                  else if(board[i][j+2][0]==oID)
                  {
                    moves.push_back({{i,j},{i,j+2}});
                    if(board[i-1][j+1][0]==oID)
                    attack2.push_back({{i,j},{i,j+2}});
                    else
                    attack1.push_back({{i,j},{i,j+2}});
                  }
                  moves.push_back({{i,j},{i,j}});
                  if(board[i-1][j-1][0]==oID)
                  attack1.push_back({{i,j},{i,j}});
                }
              }
              else if(j==2)
              {
                if(i>1)
                {
                  if(board[i-2][j-2][0]==0)
                  {
                    moves.push_back({{i,j},{i-2,j-2}});
                    if(board[i-1][j-1][0]==oID)
                    attack1.push_back({{i,j},{i-2,j-2}});
                  }
                  else if(board[i-2][j-2][0]==oID)
                  {
                    moves.push_back({{i,j},{i-2,j-2}});
                    if(board[i-1][j-1][0]==oID)
                    attack2.push_back({{i,j},{i-2,j-2}});
                    else
                    attack1.push_back({{i,j},{i-2,j-2}});
                  }
                  if(board[i-2][j][0]==0)
                  {
                    moves.push_back({{i,j},{i-2,j}});
                    if(board[i-1][j+1][0]==oID)
                    attack1.push_back({{i,j},{i-2,j}});
                  }
                  else if(board[i-2][j][0]==oID)
                  {
                    moves.push_back({{i,j},{i-2,j}});
                    if(board[i-1][j+1][0]==oID)
                    attack2.push_back({{i,j},{i-2,j}});
                    else
                    attack1.push_back({{i,j},{i-2,j}});
                  }
                }
                else if(i==1)
                {
                  if(board[i][j-2][0]==0)
                  {
                    moves.push_back({{i,j},{i,j-2}});
                    if(board[i-1][j-1][0]==oID)
                    attack1.push_back({{i,j},{i,j-2}});
                  }
                  else if(board[i][j-2][0]==oID)
                  {
                    moves.push_back({{i,j},{i,j-2}});
                    if(board[i-1][j-1][0]==oID)
                    attack2.push_back({{i,j},{i,j-2}});
                    else
                    attack1.push_back({{i,j},{i,j-2}});
                  }
                  moves.push_back({{i,j},{i,j}});
                  if(board[i-1][j+1][0]==oID)
                  attack1.push_back({{i,j},{i,j}});
                }
              }
              else if(j==3)
              {
                if(i>1)
                {
                  if(board[i-2][j-2][0]==0)
                  {
                    moves.push_back({{i,j},{i-2,j-2}});
                    if(board[i-1][j-1][0]==oID)
                    attack1.push_back({{i,j},{i-2,j-2}});
                  }
                  else if(board[i-2][j-2][0]==oID)
                  {
                    moves.push_back({{i,j},{i-2,j-2}});
                    if(board[i-1][j-1][0]==oID)
                    attack2.push_back({{i,j},{i-2,j-2}});
                    else
                    attack1.push_back({{i,j},{i-2,j-2}});
                  }
                }
                else if(i==1)
                {
                  if(board[i][j-2][0]==0)
                  {
                    moves.push_back({{i,j},{i,j-2}});
                    if(board[i-1][j-1][0]==oID)
                    attack1.push_back({{i,j},{i,j-2}});
                  }
                  else if(board[i][j-2][0]==oID)
                  {
                    moves.push_back({{i,j},{i,j-2}});
                    if(board[i-1][j-1][0]==oID)
                    attack2.push_back({{i,j},{i,j-2}});
                    else
                    attack1.push_back({{i,j},{i,j-2}});
                  }
                }
              }
            }
            else if(board[i][j][2]==1)						//downward
            {
              if(j==0)
              {
                if(i<8)
                {
                  if(board[i+2][j+2][0]==0)
                  {
                    moves.push_back({{i,j},{i+2,j+2}});
                    if(board[i+1][j+1][0]==oID)
                    attack1.push_back({{i,j},{i+2,j+2}});
                  }
                  else if(board[i+2][j+2][0]==oID)
                  {
                    moves.push_back({{i,j},{i+2,j+2}});
                    if(board[i+1][j+1][0]==oID)
                    attack2.push_back({{i,j},{i+2,j+2}});
                    else
                    attack1.push_back({{i,j},{i+2,j+2}});
                  }
                }
                else if(i==8)
                {
                  if(board[i][j+2][0]==0)
                  {
                    moves.push_back({{i,j},{i,j+2}});
                    if(board[i+1][j+1][0]==oID)
                    attack1.push_back({{i,j},{i,j+2}});
                  }
                  else if(board[i][j+2][0]==oID)
                  {
                    moves.push_back({{i,j},{i,j+2}});
                    if(board[i+1][j+1][0]==oID)
                    attack2.push_back({{i,j},{i,j+2}});
                    else
                    attack1.push_back({{i,j},{i,j+2}});
                  }
                }
              }
              else if(j==1)
              {
                if(i<8)
                {
                  if(board[i+2][j+2][0]==0)
                  {
                    moves.push_back({{i,j},{i+2,j+2}});
                    if(board[i+1][j+1][0]==oID)
                    attack1.push_back({{i,j},{i+2,j+2}});
                  }
                  else if(board[i+2][j+2][0]==oID)
                  {
                    moves.push_back({{i,j},{i+2,j+2}});
                    if(board[i+1][j+1][0]==oID)
                    attack2.push_back({{i,j},{i+2,j+2}});
                    else
                    attack1.push_back({{i,j},{i+2,j+2}});
                  }
                  if(board[i+2][j][0]==0)
                  {
                    moves.push_back({{i,j},{i+2,j}});
                    if(board[i+1][j-1][0]==oID)
                    attack1.push_back({{i,j},{i+2,j}});
                  }
                  else if(board[i+2][j][0]==oID)
                  {
                    moves.push_back({{i,j},{i+2,j}});
                    if(board[i+1][j-1][0]==oID)
                    attack2.push_back({{i,j},{i+2,j}});
                    else
                    attack1.push_back({{i,j},{i+2,j}});
                  }
                }
                else if(i==8)
                {
                  if(board[i][j+2][0]==0)
                  {
                    moves.push_back({{i,j},{i,j+2}});
                    if(board[i+1][j+1][0]==oID)
                    attack1.push_back({{i,j},{i,j+2}});
                  }
                  else if(board[i][j+2][0]==oID)
                  {
                    moves.push_back({{i,j},{i,j+2}});
                    if(board[i+1][j+1][0]==oID)
                    attack2.push_back({{i,j},{i,j+2}});
                    else
                    attack1.push_back({{i,j},{i,j+2}});
                  }
                  moves.push_back({{i,j},{i,j}});
                  if(board[i+1][j-1][0]==oID)
                  attack1.push_back({{i,j},{i,j}});
                }
              }
              else if(j==2)
              {
                if(i<8)
                {
                  if(board[i+2][j-2][0]==0)
                  {
                    moves.push_back({{i,j},{i+2,j-2}});
                    if(board[i+1][j-1][0]==oID)
                    attack1.push_back({{i,j},{i+2,j-2}});
                  }
                  else if(board[i+2][j-2][0]==oID)
                  {
                    moves.push_back({{i,j},{i+2,j-2}});
                    if(board[i+1][j-1][0]==oID)
                    attack2.push_back({{i,j},{i+2,j-2}});
                    else
                    attack1.push_back({{i,j},{i+2,j-2}});
                  }
                  if(board[i+2][j][0]==0)
                  {
                    moves.push_back({{i,j},{i+2,j}});
                    if(board[i+1][j+1][0]==oID)
                    attack1.push_back({{i,j},{i+2,j}});
                  }
                  else if(board[i+2][j][0]==oID)
                  {
                    moves.push_back({{i,j},{i+2,j}});
                    if(board[i+1][j+1][0]==oID)
                    attack2.push_back({{i,j},{i+2,j}});
                    else
                    attack1.push_back({{i,j},{i+2,j}});
                  }
                }
                else if(i==8)
                {
                  if(board[i][j-2][0]==0)
                  {
                    moves.push_back({{i,j},{i,j-2}});
                    if(board[i+1][j-1][0]==oID)
                    attack1.push_back({{i,j},{i,j-2}});
                  }
                  else if(board[i][j-2][0]==oID)
                  {
                    moves.push_back({{i,j},{i,j-2}});
                    if(board[i+1][j-1][0]==oID)
                    attack2.push_back({{i,j},{i,j-2}});
                    else
                    attack1.push_back({{i,j},{i,j-2}});
                  }
                  moves.push_back({{i,j},{i,j}});
                  if(board[i+1][j+1][0]==oID)
                  attack1.push_back({{i,j},{i,j}});
                }
              }
              else if(j==3)
              {
                if(i<8)
                {
                  if(board[i+2][j-2][0]==0)
                  {
                    moves.push_back({{i,j},{i+2,j-2}});
                    if(board[i+1][j-1][0]==oID)
                    attack1.push_back({{i,j},{i+2,j-2}});
                  }
                  else if(board[i+2][j-2][0]==oID)
                  {
                    moves.push_back({{i,j},{i+2,j-2}});
                    if(board[i+1][j-1][0]==oID)
                    attack2.push_back({{i,j},{i+2,j-2}});
                    else
                    attack1.push_back({{i,j},{i+2,j-2}});
                  }
                }
                else if(i==8)
                {
                  if(board[i][j-2][0]==0)
                  {
                    moves.push_back({{i,j},{i,j-2}});
                    if(board[i+1][j-1][0]==oID)
                    attack1.push_back({{i,j},{i,j-2}});
                  }
                  else if(board[i][j-2][0]==oID)
                  {
                    moves.push_back({{i,j},{i,j-2}});
                    if(board[i+1][j-1][0]==oID)
                    attack2.push_back({{i,j},{i,j-2}});
                    else
                    attack1.push_back({{i,j},{i,j-2}});
                  }
                }
              }
            }
          }
        }
        else if(board[i][j][0]==oID)
        oN++;
      }
    }
}

pair< pair<int,int>, pair<int,int> > bestmove(int &pN,int &oN,int &avg_pN,int &avg_oN,int board[10][4][3],vector< pair< pair<int,int> , pair<int,int> > > moves,int pID,int oID,int remaining_moves)
{

  par X;
  X.moves=moves;
  for(int i=0;i<10;i++)
  {
    for(int j=0;j<4;j++)
    memcpy(X.board[i][j],board[i][j],sizeof(board[i][j]));
  }
  X.pID=pID;
  X.oID=oID;
  X.remaining_moves=remaining_moves;

  if(cache.find(X)!=cache.end())
  {
    //cout<<"C";
    pN=cache[X].second.first;
    oN=cache[X].second.second;
    return cache[X].first;
  }

  //vector< pair< pair<int,int> , pair<int,int> > > moves,attack1,attack2;
  //calculate(moves,attack1,attack2,board,pID,oID,pN,oN);
  vector< pair< pair<int,int> , pair<int,int> > > best_moves;
  vector<int> pN_BM,oN_BM;
  //cout<<pN<<' '<<oN<<' '<<remaining_moves<<'@';
  if(remaining_moves==0)
  {
    int Board[10][4][3],bestdiff=-100,best_i=-1,bpN=0,boN=100;
    for(int i=0;i<moves.size();i++)
    {
      for(int i=0;i<10;i++)
      {
        for(int j=0;j<4;j++)
        memcpy(Board[i][j],board[i][j],sizeof(board[i][j]));
      }
      Board[moves[i].first.first][moves[i].first.second][0]=0;
      Board[moves[i].first.first][moves[i].first.second][1]=0;
      Board[moves[i].first.first][moves[i].first.second][2]=0;
      Board[moves[i].second.first][moves[i].second.second][0]=board[moves[i].first.first][moves[i].first.second][0];
      Board[moves[i].second.first][moves[i].second.second][1]=board[moves[i].first.first][moves[i].first.second][1];
      if(board[moves[i].first.first][moves[i].first.second][1]==1||(abs(moves[i].first.first-moves[i].second.first)==2&&moves[i].second.first!=0&&moves[i].second.first!=9)||((moves[i].first.first==moves[i].second.first))&&abs(moves[i].first.second-moves[i].second.second)==1)
      Board[moves[i].second.first][moves[i].second.second][2]=board[moves[i].first.first][moves[i].first.second][2];
      else
      Board[moves[i].second.first][moves[i].second.second][2]=!board[moves[i].first.first][moves[i].first.second][2];

      if(board[moves[i].first.first][moves[i].first.second][1]==2)			
      {
        if(abs(moves[i].first.first-moves[i].second.first)==2)
        {
          if(Board[(moves[i].first.first+moves[i].second.first)/2][moves[i].first.second][0]!=pID)
          {
          Board[(moves[i].first.first+moves[i].second.first)/2][moves[i].first.second][0]=0;
          Board[(moves[i].first.first+moves[i].second.first)/2][moves[i].first.second][1]=0;
          Board[(moves[i].first.first+moves[i].second.first)/2][moves[i].first.second][2]=0;
          }
        }
        else if((moves[i].first.first==moves[i].second.first)&&(moves[i].first.second==moves[i].second.second))
        {
          if(moves[i].first.first==1)
          {
            if(Board[0][moves[i].first.second][0]!=pID)
            {
              Board[0][moves[i].first.second][0]=0;
              Board[0][moves[i].first.second][1]=0;
              Board[0][moves[i].first.second][2]=0;
            }
          }
          else
          {
            if(Board[9][moves[i].first.second][0]!=pID)
            {
              Board[9][moves[i].first.second][0]=0;
              Board[9][moves[i].first.second][1]=0;
              Board[9][moves[i].first.second][2]=0;
            }
          }
        }
      }
      else if(board[moves[i].first.first][moves[i].first.second][1]==3)
      {
        int i1=moves[i].first.first;
        int j1=moves[i].first.second;
        int i2=moves[i].second.first;
        int j2=moves[i].second.second;
        if(j1==0)
        {
          if(i2==i1-2||i1+2)
          {
            if(Board[(i2+i1)/2][(j2+j1)/2][0]!=pID)
            {
              Board[(i2+i1)/2][(j2+j1)/2][0]=0;
              Board[(i2+i1)/2][(j2+j1)/2][1]=0;
              Board[(i2+i1)/2][(j2+j1)/2][2]=0;
            }
          }
          else if(i1==i2)
          {
            if(board[i1][j1][2]==0)
            {
              if(Board[i1-1][(j2+j1)/2][0]!=pID)
              {
                Board[i1-1][(j2+j1)/2][0]=0;
                Board[i1-1][(j2+j1)/2][1]=0;
                Board[i1-1][(j2+j1)/2][2]=0;
              }	
            }
            else if(board[i1][j1][2]==1)
            {
              if(Board[i1+1][(j2+j1)/2][0]!=pID)
              {
                Board[i1+1][(j2+j1)/2][0]=0;
                Board[i1+1][(j2+j1)/2][1]=0;
                Board[i1+1][(j2+j1)/2][2]=0;
              }
            }
          }
        }
        else if(j1==1)
        {
          if(i1==i2)
          {
            if(board[i1][j1][2]==0)
            {
              if(Board[i1-1][(j2+j1)/2][0]!=pID)
              {
                Board[i1-1][(j2+j1)/2][0]=0;
                Board[i1-1][(j2+j1)/2][1]=0;
                Board[i1-1][(j2+j1)/2][2]=0;
              }	
            }
            else if(board[i1][j1][2]==1)
            {
              if(Board[i1+1][(j2+j1)/2][0]!=pID)
              {
                Board[i1+1][(j2+j1)/2][0]=0;
                Board[i1+1][(j2+j1)/2][1]=0;
                Board[i1+1][(j2+j1)/2][2]=0;
              }
            }
          }
          else if(i1==i2+2||i2==i1+2)
          {
            if(j2-j1==2||j1-j2==2)
            {
              if(Board[(i2+i1)/2][(j2+j1)/2][0]!=pID)
              {
                Board[(i2+i1)/2][(j2+j1)/2][0]=0;
                Board[(i2+i1)/2][(j2+j1)/2][1]=0;
                Board[(i2+i1)/2][(j2+j1)/2][2]=0;
              }
            }
            else
            {
              if(Board[(i2+i1)/2][j1-1][0]!=pID)
              {
                Board[(i2+i1)/2][j1-1][0]=0;
                  Board[(i2+i1)/2][j1-1][1]=0;
                Board[(i2+i1)/2][j1-1][2]=0;
              }
            }
          }
        }
        else if(j1==2)
        {
          if(i1==i2)
          {
            if(board[i1][j1][2]==0)
            {
              if(Board[i1-1][(j2+j1)/2][0]!=pID)
              {
                Board[i1-1][(j2+j1)/2][0]=0;
                Board[i1-1][(j2+j1)/2][1]=0;
                Board[i1-1][(j2+j1)/2][2]=0;
              }	
            }
            else if(board[i1][j1][2]==1)
            {
              if(Board[i1+1][(j2+j1)/2][0]!=pID)
              {
                Board[i1+1][(j2+j1)/2][0]=0;
                Board[i1+1][(j2+j1)/2][1]=0;
                Board[i1+1][(j2+j1)/2][2]=0;
              }
            }
          }
          else if(i1==i2+2||i2==i1+2)
          {
            if(j2-j1==2||j1-j2==2)
            {
              if(Board[(i2+i1)/2][(j2+j1)/2][0]!=pID)
              {
                Board[(i2+i1)/2][(j2+j1)/2][0]=0;
                Board[(i2+i1)/2][(j2+j1)/2][1]=0;
                Board[(i2+i1)/2][(j2+j1)/2][2]=0;
              }
            }
            else
            {
              if(Board[(i2+i1)/2][j1+1][0]!=pID)
              {
                Board[(i2+i1)/2][j1+1][0]=0;
                  Board[(i2+i1)/2][j1+1][1]=0;
                Board[(i2+i1)/2][j1+1][2]=0;
              }
            }
          }
        }
        else if(j1==3)
        {
          if(i2==i1-2||i1+2)
          {
            if(Board[(i2+i1)/2][(j2+j1)/2][0]!=pID)
            {
              Board[(i2+i1)/2][(j2+j1)/2][0]=0;
              Board[(i2+i1)/2][(j2+j1)/2][1]=0;
              Board[(i2+i1)/2][(j2+j1)/2][2]=0;
            }
          }
          else if(i1==i2)
          {
            if(board[i1][j1][2]==0)
            {
              if(Board[i1-1][(j2+j1)/2][0]!=pID)
              {
                Board[i1-1][(j2+j1)/2][0]=0;
                Board[i1-1][(j2+j1)/2][1]=0;
                Board[i1-1][(j2+j1)/2][2]=0;
              }	
            }
            else if(board[i1][j1][2]==1)
            {
              if(Board[i1+1][(j2+j1)/2][0]!=pID)
              {
                Board[i1+1][(j2+j1)/2][0]=0;
                Board[i1+1][(j2+j1)/2][1]=0;
                Board[i1+1][(j2+j1)/2][2]=0;
              }
            }
          }
        }
      }


      vector< pair< pair<int,int> , pair<int,int> > > Moves,Attack1,Attack2;
      calculate(Moves,Attack1,Attack2,Board,pID,oID,pN,oN);   //only to calculate pN,oN
      if(oN==0)
      {
        cache[X]={moves[i],{pN,oN}};
        return moves[i];
      }
      if(pN-oN>bestdiff)
      {
        bestdiff=pN-oN;
        bpN=pN;boN=oN;
        best_i=i;
        best_moves={};
        pN_BM={};
        oN_BM={};
        best_moves.push_back(moves[i]);
        pN_BM.push_back(pN);
        oN_BM.push_back(oN);
      }
      else if(pN-oN==bestdiff)
      {
        best_moves.push_back(moves[i]);
        pN_BM.push_back(pN);
        oN_BM.push_back(oN);
      }
      /*if(i==0)
      {
      //cout<<moves[i].first.first<<' '<<moves[i].first.second<<' '<<moves[i].second.first<<' '<<moves[i].second.second;
        }*/
    }
    srand(time(NULL));
    int I=rand()%(int)best_moves.size();
    pN=pN_BM[I];
    oN=oN_BM[I];
    cache[X]={best_moves[I],{pN,oN}};
    return best_moves[I];
  }
  else
  {
    int Board[10][4][3],bestdiff=-100,best_i=-1,bpN=0,boN=100;
    for(int i=0;i<moves.size();i++)
    {
      for(int i=0;i<10;i++)
      {
        for(int j=0;j<4;j++)
        memcpy(Board[i][j],board[i][j],sizeof(board[i][j]));
      }
      /*for(int i=0;i<10;i++)
      {
        for(int j=0;j<4;j++)
        {
          for(int k=0;k<3;k++)
          cout<<Board[i][j][k];
          cout<<' ';
        }
        cout<<'\n';
      }*/
      Board[moves[i].first.first][moves[i].first.second][0]=0;
      Board[moves[i].first.first][moves[i].first.second][1]=0;
      Board[moves[i].first.first][moves[i].first.second][2]=0;
      Board[moves[i].second.first][moves[i].second.second][0]=board[moves[i].first.first][moves[i].first.second][0];
      Board[moves[i].second.first][moves[i].second.second][1]=board[moves[i].first.first][moves[i].first.second][1];
      if(board[moves[i].first.first][moves[i].first.second][1]==1||(abs(moves[i].first.first-moves[i].second.first)==2&&moves[i].second.first!=0&&moves[i].second.first!=9)||((moves[i].first.first==moves[i].second.first))&&abs(moves[i].first.second-moves[i].second.second)==1)
      Board[moves[i].second.first][moves[i].second.second][2]=board[moves[i].first.first][moves[i].first.second][2];
      else
      Board[moves[i].second.first][moves[i].second.second][2]=!board[moves[i].first.first][moves[i].first.second][2];

      if(board[moves[i].first.first][moves[i].first.second][1]==2)			
      {
        if(abs(moves[i].first.first-moves[i].second.first)==2)
        {
          if(Board[(moves[i].first.first+moves[i].second.first)/2][moves[i].first.second][0]!=pID)
          {
          Board[(moves[i].first.first+moves[i].second.first)/2][moves[i].first.second][0]=0;
          Board[(moves[i].first.first+moves[i].second.first)/2][moves[i].first.second][1]=0;
          Board[(moves[i].first.first+moves[i].second.first)/2][moves[i].first.second][2]=0;
          }
        }
        else if((moves[i].first.first==moves[i].second.first)&&(moves[i].first.second==moves[i].second.second))
        {
          if(moves[i].first.first==1)
          {
            if(Board[0][moves[i].first.second][0]!=pID)
            {
              Board[0][moves[i].first.second][0]=0;
              Board[0][moves[i].first.second][1]=0;
              Board[0][moves[i].first.second][2]=0;
            }
          }
          else
          {
            if(Board[9][moves[i].first.second][0]!=pID)
            {
              Board[9][moves[i].first.second][0]=0;
              Board[9][moves[i].first.second][1]=0;
              Board[9][moves[i].first.second][2]=0;
            }
          }
        }
      }
      else if(board[moves[i].first.first][moves[i].first.second][1]==3)
      {
        int i1=moves[i].first.first;
        int j1=moves[i].first.second;
        int i2=moves[i].second.first;
        int j2=moves[i].second.second;
        if(j1==0)
        {
          if(i2==i1-2||i1+2)
          {
            if(Board[(i2+i1)/2][(j2+j1)/2][0]!=pID)
            {
              Board[(i2+i1)/2][(j2+j1)/2][0]=0;
              Board[(i2+i1)/2][(j2+j1)/2][1]=0;
              Board[(i2+i1)/2][(j2+j1)/2][2]=0;
            }
          }
          else if(i1==i2)
          {
            if(board[i1][j1][2]==0)
            {
              if(Board[i1-1][(j2+j1)/2][0]!=pID)
              {
                Board[i1-1][(j2+j1)/2][0]=0;
                Board[i1-1][(j2+j1)/2][1]=0;
                Board[i1-1][(j2+j1)/2][2]=0;
              }	
            }
            else if(board[i1][j1][2]==1)
            {
              if(Board[i1+1][(j2+j1)/2][0]!=pID)
              {
                Board[i1+1][(j2+j1)/2][0]=0;
                Board[i1+1][(j2+j1)/2][1]=0;
                Board[i1+1][(j2+j1)/2][2]=0;
              }
            }
          }
        }
        else if(j1==1)
        {
          if(i1==i2)
          {
            if(board[i1][j1][2]==0)
            {
              if(Board[i1-1][(j2+j1)/2][0]!=pID)
              {
                Board[i1-1][(j2+j1)/2][0]=0;
                Board[i1-1][(j2+j1)/2][1]=0;
                Board[i1-1][(j2+j1)/2][2]=0;
              }	
            }
            else if(board[i1][j1][2]==1)
            {
              if(Board[i1+1][(j2+j1)/2][0]!=pID)
              {
                Board[i1+1][(j2+j1)/2][0]=0;
                Board[i1+1][(j2+j1)/2][1]=0;
                Board[i1+1][(j2+j1)/2][2]=0;
              }
            }
          }
          else if(i1==i2+2||i2==i1+2)
          {
            if(j2-j1==2||j1-j2==2)
            {
              if(Board[(i2+i1)/2][(j2+j1)/2][0]!=pID)
              {
                Board[(i2+i1)/2][(j2+j1)/2][0]=0;
                Board[(i2+i1)/2][(j2+j1)/2][1]=0;
                Board[(i2+i1)/2][(j2+j1)/2][2]=0;
              }
            }
            else
            {
              if(Board[(i2+i1)/2][j1-1][0]!=pID)
              {
                Board[(i2+i1)/2][j1-1][0]=0;
                  Board[(i2+i1)/2][j1-1][1]=0;
                Board[(i2+i1)/2][j1-1][2]=0;
              }
            }
          }
        }
        else if(j1==2)
        {
          if(i1==i2)
          {
            if(board[i1][j1][2]==0)
            {
              if(Board[i1-1][(j2+j1)/2][0]!=pID)
              {
                Board[i1-1][(j2+j1)/2][0]=0;
                Board[i1-1][(j2+j1)/2][1]=0;
                Board[i1-1][(j2+j1)/2][2]=0;
              }	
            }
            else if(board[i1][j1][2]==1)
            {
              if(Board[i1+1][(j2+j1)/2][0]!=pID)
              {
                Board[i1+1][(j2+j1)/2][0]=0;
                Board[i1+1][(j2+j1)/2][1]=0;
                Board[i1+1][(j2+j1)/2][2]=0;
              }
            }
          }
          else if(i1==i2+2||i2==i1+2)
          {
            if(j2-j1==2||j1-j2==2)
            {
              if(Board[(i2+i1)/2][(j2+j1)/2][0]!=pID)
              {
                Board[(i2+i1)/2][(j2+j1)/2][0]=0;
                Board[(i2+i1)/2][(j2+j1)/2][1]=0;
                Board[(i2+i1)/2][(j2+j1)/2][2]=0;
              }
            }
            else
            {
              if(Board[(i2+i1)/2][j1+1][0]!=pID)
              {
                Board[(i2+i1)/2][j1+1][0]=0;
                  Board[(i2+i1)/2][j1+1][1]=0;
                Board[(i2+i1)/2][j1+1][2]=0;
              }
            }
          }
        }
        else if(j1==3)
        {
          if(i2==i1-2||i1+2)
          {
            if(Board[(i2+i1)/2][(j2+j1)/2][0]!=pID)
            {
              Board[(i2+i1)/2][(j2+j1)/2][0]=0;
              Board[(i2+i1)/2][(j2+j1)/2][1]=0;
              Board[(i2+i1)/2][(j2+j1)/2][2]=0;
            }
          }
          else if(i1==i2)
          {
            if(board[i1][j1][2]==0)
            {
              if(Board[i1-1][(j2+j1)/2][0]!=pID)
              {
                Board[i1-1][(j2+j1)/2][0]=0;
                Board[i1-1][(j2+j1)/2][1]=0;
                Board[i1-1][(j2+j1)/2][2]=0;
              }	
            }
            else if(board[i1][j1][2]==1)
            {
              if(Board[i1+1][(j2+j1)/2][0]!=pID)
              {
                Board[i1+1][(j2+j1)/2][0]=0;
                Board[i1+1][(j2+j1)/2][1]=0;
                Board[i1+1][(j2+j1)/2][2]=0;
              }
            }
          }
        }
      }
            /*if(remaining_moves==1)
            {
            cout<<'\n';
            for(int i=0;i<10;i++)
      {
            for(int j=0;j<4;j++)
            {
                for(int k=0;k<3;k++)
                cout<<Board[i][j][k];
                cout<<' ';
            }
            cout<<'\n';
      }
            }*/

            vector< pair< pair<int,int> , pair<int,int> > > Moves,Attack1,Attack2;
      calculate(Moves,Attack1,Attack2,Board,oID,pID,oN,pN);//only to calculate pN,oN

      if(oN==0)
      {
        cache[X]={moves[i],{pN,oN}};
        return moves[i];
      }

      int tem1,tem2;
      bestmove(oN,pN,tem1,tem2,Board,Moves,oID,pID,remaining_moves-1);
      if(pN-oN>bestdiff)
      {
        bestdiff=pN-oN;
        bpN=pN;boN=oN;
        best_i=i;
        best_moves={};
        pN_BM={};
        oN_BM={};
        best_moves.push_back(moves[i]);
        pN_BM.push_back(pN);
        oN_BM.push_back(oN);
      }
      else if(pN-oN==bestdiff)			//Consider attack and defensive positions
      {
        best_moves.push_back(moves[i]);
        pN_BM.push_back(pN);
        oN_BM.push_back(oN);
      }
    }
    if(best_moves.size()==1)
    {
        pN=pN_BM[0];
        oN=oN_BM[0];
        cache[X]={best_moves[0],{pN,oN}};
      return best_moves[0];
    }
      else
    {
      int tem1,tem2;
      pair< pair<int,int>,pair<int,int> >M=bestmove(pN,oN,tem1,tem2,board,best_moves,pID,oID,remaining_moves-1);
      for(int j=0;j<best_moves.size();j++)
      {
          if(best_moves[j]==M)
          {
              pN=pN_BM[j];
              oN=oN_BM[j];
              return M;
          }
      }
    }
    /*srand(time(NULL));
    int I=rand()%(int)best_moves.size();
    pN=pN_BM[I];
    oN=oN_BM[I];
    cache[X]={best_moves[I],{pN,oN}};
    return best_moves[I];*/
  }
}

int main()
{
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int board[10][4][3],totalmoves,pID,oID,pN,oN,avg_oN,avg_pN;
    vector< pair< pair<int,int> , pair<int,int> > > moves,attack1,attack2;
    //map< pair< pair<int,int>,pair<int,int> >,pair<int,int> > Erase;
    for(int i=0;i<10;i++)
    {
      for(int j=0;j<4;j++)
      {
        cin>>board[i][j][0];
        board[i][j][2]=board[i][j][0]%10;
        board[i][j][0]/=10;
        board[i][j][1]=board[i][j][0]%10;
        board[i][j][0]/=10;
      }
    }
    cin>>totalmoves>>pID;

    if(pID==1)
    oID=2;
    else
    oID=1;

    calculate(moves,attack1,attack2,board,pID,oID,pN,oN);

    //int scope=((pN+oN<16)?4:3);
    int scope=5-(pN+oN+2)/8;

    pair< pair<int,int>,pair<int,int> > M=bestmove(pN,oN,avg_pN,avg_oN,board,moves,pID,oID,((100-totalmoves-1>scope)?scope:(100-totalmoves-1)));

    cout<<M.first.first<<' '<<M.first.second<<'\n'<<M.second.first<<' '<<M.second.second<<'\n'<<pN<<' '<<oN<<'#';

    //calculate(moves,attack1,attack2,board,pID,oID,pN,oN);

    /*for(int i=0;i<(int)moves.size();i++)
    {
      cout<<moves[i].first.first<<' '<<moves[i].first.second<<' '<<moves[i].second.first<<' '<<moves[i].second.second<<'\n';
    }
    cout<<"\n\n";
    for(int i=0;i<(int)attack1.size();i++)
    {
      cout<<attack1[i].first.first<<' '<<attack[i].first.second<<' '<<attack1[i].second.first<<' '<<attack1[i].second.second<<'\n';
    }
    cout<<"\n\n";
    for(int i=0;i<(int)attack2.size();i++)
    {
      cout<<attack2[i].first.first<<' '<<attack2[i].first.second<<' '<<attack2[i].second.first<<' '<<attack2[i].second.second<<'\n';
    }*/

    /*srand(time(NULL));

    //Attack

    //Double Attack
    if(!attack2.empty())
    {
      vector< pair< pair<int,int>, pair<int,int> > > safemoves;
      for(int i=0;i<attack2.size();i++)
      {
        if(safe(attack2[i].second.first,attack2[i].second.second,board,pID,oID))
        safemoves.push_back(attack2[i]);
      }
      if(!safemoves.empty())
      {
        int I=rand()%(int)safemoves.size();
        cout<<safemoves[I].first.first<<' '<<safemoves[I].first.second<<'\n'<<safemoves[I].second.first<<' '<<safemoves[I].second.second;
        return 0;
      }
      int I=rand()%(int)attack2.size();
      cout<<attack2[I].first.first<<' '<<attack2[I].first.second<<'\n'<<attack2[I].second.first<<' '<<attack2[I].second.second;
      return 0;
    }

    //Single Attack
    if(!attack1.empty())
    {
      vector< pair< pair<int,int>, pair<int,int> > > safemoves;
      for(int i=0;i<attack1.size();i++)
      {
        if(safe(attack1[i].second.first,attack1[i].second.second,board,pID,oID))
        safemoves.push_back(attack1[i]);
      }
      if(!safemoves.empty())
      {
        int I=rand()%(int)safemoves.size();
        cout<<safemoves[I].first.first<<' '<<safemoves[I].first.second<<'\n'<<safemoves[I].second.first<<' '<<safemoves[I].second.second;
        return 0;
      }
      int I=rand()%(int)attack1.size();
      cout<<attack1[I].first.first<<' '<<attack1[I].first.second<<'\n'<<attack1[I].second.first<<' '<<attack1[I].second.second;
      return 0;
    }

    //Defense
    vector< pair< pair<int,int>, pair<int,int> > > defense;
    for(int i=0;i<moves.size();i++)
    {
      if(!safe(moves[i].first.first,moves[i].first.second,board,pID,oID)&&safe(moves[i].second.first,moves[i].second.second,board,pID,oID))
      defense.push_back(moves[i]);
    }
    if(!defense.empty())
    {
      int I=rand()%(int)defense.size();
      cout<<defense[I].first.first<<' '<<defense[I].first.second<<'\n'<<defense[I].second.first<<' '<<defense[I].second.second;
      return 0;
    }

    //Random Move
    vector< pair< pair<int,int>, pair<int,int> > > safemoves;
    for(int i=0;i<moves.size();i++)
    {
      if(safe(moves[i].second.first,moves[i].second.second,board,pID,oID))
      safemoves.push_back(moves[i]);
    }
    if(!safemoves.empty())
    {
      int I=rand()%(int)safemoves.size();
      cout<<safemoves[I].first.first<<' '<<safemoves[I].first.second<<'\n'<<safemoves[I].second.first<<' '<<safemoves[I].second.second;
      return 0;
    }
    int I=rand()%(int)moves.size();
    cout<<moves[I].first.first<<' '<<moves[I].first.second<<'\n'<<moves[I].second.first<<' '<<moves[I].second.second;*/
}

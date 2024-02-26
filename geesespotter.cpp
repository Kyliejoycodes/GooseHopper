#include "geesespotter_lib.h"
#include <iostream>

//functions tested in first submissison- create_board(), clean_board(), print_board(), hide_board(), mark()-only submiot this file
//to test- g++ -std=c++11 geesepotter.cpp geesespotter_lib.cpp -o main
//.\main to run test file

//How it works:
//grid made from array, each spot market with *, geese randomly placed in grid
//per turn, select S how, M ark/(unmark), then select coordinates to perform action at

//show:
//if place where goose is selected, game over, styart new game
//no goose in spot, replace * with field value(0,8)
//if no goose in neghbouring spot, unmarked naighbour spots are also replaced with field value

//mark:
//you mark a field if you think a goose is there
//if selected, change M to * or * to M
//ONLY MARKED FIELDS CAN BE UNMARKED

//print board after each action

//won if all no goose spots are shown

//after won/lost restart game by asking board dimensions

//R estart or Q uit available

char *create_board(std::size_t x_dim, std::size_t y_dim){
    //char *board= new char[x_dim*y_dim];
    char *board{new char[x_dim*y_dim]};

    for(int x=0;x<(x_dim*y_dim); x++){
        board[x]= 0;
    }
    
    return board;
}

//deallocate board(wipe from memory)
void clean_board(char *board){
    delete[] board;
    board= nullptr;
}

void print_board(char *board, std::size_t x_dim, std::size_t y_dim){
    
    //std::cout<<"enter print board"<<std::endl;
    int size{};
    size = (x_dim*y_dim);
    for(int x=0 ; x<size ; x++){

        //next line on grid
        if((x%x_dim) == 0 ){
            std::cout<<' '<<std::endl;
        }

        //if Marked tile
        if((board[x] & marked_mask())==marked_mask()){
            std::cout<<'M';
        }

        //if Hidden tile
        else if((board[x]&hidden_mask())==hidden_mask()){
            std::cout<<'*';
        }

        //value tile
        else{
            int temp= board[x] & value_mask();
            int *temp2{&temp};
            std::cout<< *temp2;
        }

    }

    std::cout<<' '<<std::endl;
}

void hide_board(char *board, std::size_t x_dim, std::size_t y_dim){
    for(int x=0; x<(x_dim*y_dim);x++){
        board[x]=board[x]^hidden_mask();
    }

}

int mark(char *board, std::size_t x_dim, std::size_t y_dim, std::size_t x_loc, std::size_t y_loc){
    char location{};
    location = y_loc*x_dim + x_loc;

    //if hidden flip the mask bit
    //if(board[location]&hidden_mask()==1){
        //return 2;
    //    board[location]= board[location]^marked_mask();
    //}
    if((board[location]&hidden_mask())==0){
          return 2;
    }
    else{
        board[location]= board[location]^marked_mask();
        return 0;
    }
    //if(board[location]&marked_mask()==1){
    //    board[location]= board[location]^marked_mask();
    //}
    //else if(board[location]&marked_mask()==0){
    //    board[location]= board[location]^marked_mask();
    //}


}


//required for second submission:
bool in_bounds(char *board, std::size_t x_dim, std::size_t y_dim, std::size_t x_loc, std::size_t y_loc){
    if((x_loc<x_dim) && (x_loc>=0)){
        return true;
    }
    else{
        return false;
    }
    
    if((y_loc<y_dim) && (y_loc>=0)){
        return true;
    }
    else{
        return false;
    }
}

void compute_neighbours(char *board, std::size_t x_dim, std::size_t y_dim){
    //if not 9- compute number of adjacent geese
    for(int i=0; i<(x_dim*y_dim); i++){
        int x_coord = i%x_dim;
        int y_coord = i/y_dim;
        int x = y_coord*x_dim + x_coord;
        //int geese = 0;

        if((board[i]&value_mask())!=9){

            if(in_bounds( board,x_dim, y_dim, x_coord+1, y_coord)==true){
                //if value is not marked and hidden, and a goose, add cto goose counter
                if(((board[i+1]&marked_mask())==0) && ((board[i+1]&value_mask())==9)){
                    //geese++;
                    board[i]= board[i]+1;
                }
            }

            if(in_bounds(board,x_dim, y_dim, x_coord-1, y_coord)==true){
                if(((board[i-1]&marked_mask())==0) && ((board[i-1]&value_mask())==9)){
                    //geese++;
                    board[i]= board[i]+1;
                }
            }

            if(in_bounds(board,x_dim, y_dim, x_coord, y_coord+1)==true){
                if(((board[i+x_dim]&marked_mask())==0) && ((board[i+x_dim]&value_mask())==9)){
                    //geese++;
                    board[i]= board[i]+1;
                }
            }

            if(in_bounds(board,x_dim, y_dim, x_coord, y_coord-1)==true){
                if(((board[i-x_dim]&marked_mask())==0) && ((board[i-x_dim]&value_mask())==9)){
                    //geese++;
                    board[i]= board[i]+1;
                }
            }

            if(in_bounds(board,x_dim, y_dim, x_coord+1, y_coord+1)==true){
                if(((board[i+1+x_dim]&marked_mask())==0) && ((board[i+1+x_dim]&value_mask())==9)){
                    //geese++;
                    board[i]= board[i]+1;
                }
            }

            if(in_bounds(board,x_dim, y_dim, x_coord-1, y_coord-1)==true){
                if(((board[i-1-x_dim]&marked_mask())==0) && ((board[i-1-x_dim]&value_mask())==9)){
                    //geese++;
                    board[i]= board[i]+1;
                }
            }

            if(in_bounds(board,x_dim, y_dim, x_coord+1, y_coord-1)==true){
                if(((board[i+1-x_dim]&marked_mask())==0) && ((board[i+1-x_dim]&value_mask())==9)){
                    //geese++;
                    board[i]= board[i]+1;
                }
            }

            if(in_bounds(board,x_dim, y_dim, x_coord-1, y_coord+1)==true){
                if(((board[i-1+x_dim]&marked_mask())==0) && ((board[i-1+x_dim]&value_mask())==9)){
                    //geese++;
                    board[i]= board[i]+1;
                }
            }

            //board[i]=board[i]+geese;

         }

        //value at index equals amount of geese
        //board[i]=board[i]+geese;

    }
}

bool is_game_won(char *board, std::size_t x_dim, std::size_t y_dim){
    int x = 0;
    int goose_counter{};

    while(x<(x_dim*y_dim)){

        //if goose
        if((board[x]&value_mask())==9){
            //goose_counter++;
            //if goose hidden

            if((board[x]&hidden_mask())==32){
                ++x;
                goose_counter++;
            }

            //not hidden goose:(-lost
            else{
                return false;
            }
        }

        //if not goose
        else{

            //value is revealed
            if((board[x]&hidden_mask())==0){
                ++x;
            }

            else{
                return false;
            }
        }

        //IF EVERY SPOT HAS A GOOSE - EX: 5x5, 25 geese
        if(goose_counter==(x_dim*y_dim)){
            return false;
        }
        //does this need an else?
    }

    //every value meets conditions - WIN    
        return true;

}

int reveal(char *board, std::size_t x_dim, std::size_t y_dim, std::size_t x_loc, std::size_t y_loc){
    int x{};
    x = y_loc*x_dim + x_loc;


    //if marked return 1 - marked fields can only be unmarked
    if((board[x]&marked_mask())==16){
         return 1;

    }

    //reveal if hidden and unmarked
    else if(((board[x]&hidden_mask())==32) && ((board[x]&marked_mask())==0)){
                board[x]=board[x]^hidden_mask();
    }

    //if value already revealed, return 2
    else if((board[x]&hidden_mask())==0){
        return 2;
     }

    //if value is a goose
    else if((board[x]&value_mask())==9){

        //make sure it is revealed and return 9
        if((board[x]&hidden_mask())==32){
            board[x]=board[x]^hidden_mask();
        }
        return 9;
    }

    //all other cases return 0
    else{
        return 0;
    }

    //if value is 0 and revealed
    if(((board[x]&value_mask())==0) && ((board[x]&hidden_mask())==0)){
        //reveal values of all unmarked neighbouring fields and in bounds

        if(in_bounds( board,x_dim, y_dim, x_loc+1, y_loc)==true){
            //if value is not marked and hidden, reveal
            if(((board[x+1]&marked_mask())==0) && ((board[x+1]&hidden_mask())==32)){
                board[x+1]=board[x+1]^hidden_mask();
            }
        }

        if(in_bounds(board,x_dim, y_dim, x_loc-1, y_loc)==true){
            if(((board[x-1]&marked_mask())==0) && ((board[x-1]&hidden_mask())==32)){
                board[x-1]=board[x-1]^hidden_mask();
            }
        }

        if(in_bounds(board,x_dim, y_dim, x_loc, y_loc+1)==true){
            if(((board[x+x_dim]&marked_mask())==0) && ((board[x+x_dim]&hidden_mask())==32)){
                board[x+x_dim]=board[x+x_dim]^hidden_mask();
            }
        }

        if(in_bounds(board,x_dim, y_dim, x_loc, y_loc-1)==true){
            if(((board[x-x_dim]&marked_mask())==0) && ((board[x-x_dim]&hidden_mask())==32)){
                board[x-x_dim]=board[x-x_dim]^hidden_mask();
             }
        }

        if(in_bounds(board,x_dim, y_dim, x_loc+1, y_loc+1)==true){
            if(((board[x+1+x_dim]&marked_mask())==0) && ((board[x+1+x_dim]&hidden_mask())==32)){
               board[x+1+x_dim]=board[x+1+x_dim]^hidden_mask();
            }
        }

        if(in_bounds(board,x_dim, y_dim, x_loc-1, y_loc-1)==true){
            if(((board[x-1-x_dim]&marked_mask())==0) && ((board[x-1-x_dim]&hidden_mask())==32)){
                board[x-1-x_dim]=board[x-1-x_dim]^hidden_mask();
            }
        }

        if(in_bounds(board,x_dim, y_dim, x_loc+1, y_loc-1)==true){
            if(((board[x+1-x_dim]&marked_mask())==0) && ((board[x+1-x_dim]&hidden_mask())==32)){
                board[x+1-x_dim]=board[x+1-x_dim]^hidden_mask();
            }
        }

        if(in_bounds(board,x_dim, y_dim, x_loc-1, y_loc+1)==true){
            if(((board[x-1+x_dim]&marked_mask())==0) && ((board[x-1+x_dim]&hidden_mask())==32)){
                board[x-1+x_dim]=board[x-1+x_dim]^hidden_mask();
            }
        }

        }   
    return 0;
}
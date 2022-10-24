#include <iostream>
#include <vector>
#include <string>
#include <cmath>

struct puzzle_t {
    int width;
    int height;
    std::vector<int> board;
    std::vector<std::vector<int>> vertical_conditions;
    std::vector<std::vector<int>> horizontal_conditions;
    int &get(const int x, const int y){
        return board[y*width + x];
    }
    int get(const int x, const int y) const{
        return board.at(y*width + x);
    }
};


double evaluate(const puzzle_t & puzzle){
    return 0.0;
}

std::ostream &operator<<(std::ostream &o, const puzzle_t &puzzle) {
    for (int y = 0; y < puzzle.height; y++){

        o << "|";
        for (int x = 0; x < puzzle.width; x++){
            auto &val = puzzle.board[y*puzzle.width + x];
            o << "\t" << ((val>0)? "X":" ") << "|";
        }
        o << std::endl;
    }
    return o;
}

void print_nonogram(const puzzle_t table) {
    std::cout << "|";
    for(int i =0; i < table.width; i++){
        int left_spaces = 4 - table.horizontal_conditions[i].size();
        int right_spaces = 4 - table.horizontal_conditions[i].size();
        std::cout << std::string(left_spaces, ' ');
        for (int c =0; c<table.horizontal_conditions[i].size(); c++){
            std::cout <<table.horizontal_conditions[i][c] << ",";
        }
        std::cout << std::string(right_spaces, ' ') << "|";
    }
    std::cout << std::endl;
    for(int i = 0; i<table.height;i++){
        for(int c=0; c<table.vertical_conditions[i].size(); c++){
            std::cout <<table.vertical_conditions[i][c] << ", ";
        }
        for(int y=0; y<table.width;y++){
            auto &val = table.board[i*table.width + y];
            std::cout << "\t" << ((val>0)? "X":" ") << "|";
        }
        std::cout << std::endl;
        }


    }

int evaluate_puzzle(const puzzle_t puzzle){
    std::vector<std::vector<int>> errors = {};
    std::vector<int> vertical_errors = {};
    std::vector<int> horizontal_errors = {};
    for(int i = 0; i < puzzle.height; i++){

        std::vector<int> values = {};
        int value =0;
        for(int y = 0; y < puzzle.width; y++){

            int elem = puzzle.board[puzzle.width * i + y];
//            std::cout << value << std::endl;
            if(elem == 1){
                value += 1;
            }

            if(elem == 0 or y == puzzle.width - 1){

                if (value != 0){values.push_back(value); }
//                std::cout << value << std::endl;
                value = 0;
            }



        }
        if (values != puzzle.vertical_conditions[i]){
            vertical_errors.push_back(i);
        }
    }
    for(int i = 0; i < puzzle.width; i++){

        std::vector<int> values = {};
        int value =0;
        for(int y = i; y <= (puzzle.width*(puzzle.height- 1)) + i; y+=puzzle.width){
            if ( i == 1) {
                int z = 2;
            }
            int elem = puzzle.board[y];
//            std::cout << value << std::endl;
            if(elem == 1){
                value += 1;
            }

            if(elem == 0 or y == (puzzle.width*(puzzle.height - 1)) + i){

                if (value != 0){values.push_back(value); }
//                std::cout << value << std::endl;
                value = 0;
            }



        }

        if (values != puzzle.horizontal_conditions[i]){
            horizontal_errors.push_back(i);
        }
    }
    errors.push_back(vertical_errors);
    errors.push_back(horizontal_errors);
    int number_of_errors = errors.at(0).size() + errors.at(1).size();
    return number_of_errors;
}

bool get_table_comb(puzzle_t &puzzle) {
    int i = 0;
    for (; i < puzzle.board.size(); i++) {
        if (puzzle.board[i] == 0) {
            puzzle.board[i] = -1;
            break;
        } else if (puzzle.board[i] == -1) {
            puzzle.board[i] = 0;
        }
    }
    return (i != puzzle.board.size());
}

bool next_solution(puzzle_t &puzzle) {
    int i = 0;
    for (; i < puzzle.board.size(); i++) {
        if (puzzle.board[i] == 0) {
            puzzle.board[i] = 1;
            break;
        } else {
            puzzle.board[i] = 0;
        }
    }
    return (i != puzzle.board.size());
}

//int checkout_combinations(int h, int w, std::vector<int> solution){
//    for(int i = 0; i < h*w; i++){
//        std::vector<int> proposed_solution = get_table_comb(h, w);
//        if(solution == proposed_solution){
//            return 1;
//        }
//    }
//}


int main() {
    puzzle_t tabela;
    tabela.width = 10;
    tabela.height = 10;
    tabela.vertical_conditions = {
            {3, 5}, {1,5}, {1, 6}, {5}, {2,4,1}, {2, 1}, {3}, {5, 1}, {1}, {2, 1, 1}
    };

    tabela.horizontal_conditions = {
            {1, 4, 1}, {3, 4, 1}, {1, 3}, {1, 1}, {3, 1}, {5}, {5,1}, {4, 1, 1}, {5, 1}, {3}
    };
    tabela.board = {
            1,1,1,0,0,1,1,1,1,1,
             0,1,0,0,0,1,1,1,1,1,
             0,1,0,0,1,1,1,1,1,1,
             0,0,0,0,1,1,1,1,1,0,
             1,1,0,1,1,1,1,0,1,0,
             1,1,0,0,0,0,0,1,0,0,
             1,1,1,0,0,0,0,0,0,0,
             1,1,1,1,1,0,0,1,0,0,
             0,0,1,0,0,0,0,0,0,0,
             1,1,0,0,0,0,1,0,1,0
    };


//
//    print_nonogram(tabela);

//    int err = evaluate_puzzle(tabela);
//    std::cout << "error" << std::endl;
//    std::cout << err << std::endl;

    // zad 2

    puzzle_t tabela_2;
    tabela_2.width = 3;
    tabela_2.height = 3;
    tabela_2.vertical_conditions = {
            {3}, {}, {1}
    };

    tabela_2.horizontal_conditions = {
            {1}, {1 , 1}, {1}
    };
    tabela_2.board = {
            0,0,0,
            0, 0, 0,
            0, 0, 0,
    };
    int err_2 = evaluate_puzzle(tabela_2);

    std::cout << "errors" << std::endl;
    // funkcja kosztu
    std::cout << err_2 << std::endl;
    int n = 0;
    while (next_solution(tabela_2)) {
        int errors = evaluate_puzzle(tabela_2);
        if ((n % 128) == 0) {
            std::cout << n << " : " << errors << std::endl << tabela_2 << std::endl;
        }
        if (errors == 0) {
            std::cout << tabela_2 << std::endl;
            break;
        }
        n++;
    }

    return 0;
}

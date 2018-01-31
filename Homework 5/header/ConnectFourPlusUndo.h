#ifndef CONNECTFOURPLUSUNDO_H
    #define CONNECTFOURPLUSUNDO_H 
    #include "./ConnectFourAbstract.h"
    namespace MuazKurt
    {
        class ConnectFourPlusUndo : public ConnectFourAbstract
        {
        public:
            //Caller Base class constructer
            /*
                1 default valued parameter constructer.
            */
            
            ConnectFourPlusUndo(int square = 5);
            
            /*
                2 parameter constructer.
            */
            ConnectFourPlusUndo(int rectHeight, int rectWidth);

            /*
                Copy constructer.
            */
            ConnectFourPlusUndo(const ConnectFourPlusUndo & other);

            /*
                Assigns two objects with Base class's assignment operator and it's way.
            */
            const ConnectFourPlusUndo & operator =(const ConnectFourPlusUndo & other);

            /*
                Destructer
            */
            ~ConnectFourPlusUndo();

            /*
                Redeclaring the AI' s play function for make possible to set history.
                Calls base class' s play function for making same play operation.
            */
            void play();

            /*
                Redeclaring the play function for make possible to set history.
            */
            void play(Cell IDONTNEEDIT);
            
            /*
                This does almost the same thing as base class.
                One difference, if undo declared, then passes the current user.
            */
            void MakeMove();

            /*
                Does the same thing as base class.
                Only calls it's redeclared functions.
            */
            void PlayGame();

            /*
                Parses formated string with base class parseInput function,
                then reads the history info after offset of the string.
            */
            int parseInput(const std::string & input);
            
            /*
                Opens File and reads info from it.
            */
            void Load(const std::string & filename);
      
            /*
                Creats a formated string from itself.
            */
            void toString(std::string & output) const;

            /*
                Saves a formated string to a file.
            */
            void Save(const std::string & filename) const;
        private:
            int ** history;
            int _size;
            int _capacity;
            bool _nowUndo;

            /*
                Deletes allocated memory.
            */
            void Alzheimer();

            /*
                Allocates memory for using as history array.
            */
            void CreateHistory();
        };
    }
#endif
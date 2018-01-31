#ifndef CELL_H
    #define CELL_H 
    #include <iostream>
    #include <fstream>
    namespace MuazKurt
    {
        class Cell
        {
            public:
                //Constructer
                    /*
                        Declares that:
                            positionX = 'a'
                            positionY = 0
                            info = 0
                    */
                    Cell(int inside = 0);
                    
                    /*
                        Declares that:
                            info = 0
                        and
                        Calls:
                            setCell(input, value);
                    */
                    Cell(int value, char input);
                    
                    /*
                        Calls
                            setCell(input, value);
                            setCell(info);
                    */
                    Cell(int value, char input, int info);
                //      ~Constructer
                //Destructer
                    ~Cell();
                //      ~Destructer
                //Operators
                    //Bool
                        /* 
                            == Compares objects info
                        */
                        bool operator ==(const Cell & other) const;

                        /*
                            !=
                        */
                        bool operator !=(const Cell & other) const;
                    //
                    //Incrimnet
                        /*
                            ++ user1-> user2 | AI -> empty -> user1
                        */
                        Cell operator++(int);
                        const Cell & operator++();
                    //
                    //Decriment
                        /*
                            -- empty -> user1 -> user2 | AI -> empty
                        */
                        Cell operator--(int);
                        const Cell & operator--();

                    //
                //      ~Operators
                //Setter
                    /*
                        Checks info for legal or not.
                        Then checks if the cell is empty or not.
                        if empty fills the cell.
                        if filled Then checks if update is legal or not.
                    */
                    void setCell(int info);
                //      ~Setter
                //Getter
                    /*
                        Returns positionX
                    */
                    char getRow() const;
                    /*
                        Returns positionY
                    */
                    int getColumn() const;
                    /*
                        Returns Inside
                    */
                    int getInside() const;
                    /*
                        Returns How many LivingCells alive.
                    */
                    inline static int getLivingCells() { return LivingCells; }
                //      ~Getter
            private:
                inline void LivingCellDestroyed()   { --LivingCells; }
                inline void LivingCellUpdate()	    { ++LivingCells; }
                /*
                    Declaring Cell position
                */
                void setCell(char input, int value);
                /*
                    Location info
                */
                char positionX;
                int positionY;
                /*
                    Inside information.
                */
                int Inside;
                /*
                    Living Cells.
                */
                static int LivingCells;
            public:
                //Streams
                    /*
                        << writes the output ostream file like:
                            'x', 'X', 'O', 'o', ' ', '.'
                    */
                    friend std::ostream & operator <<(std::ostream & file, const Cell & me);
                    

                    /*
                        >> gets inputs '*', ' ' and '\n'
                            and updates them like my inside format.
                    */
                    friend std::istream & operator >>(std::istream & file, Cell & me);
                    
                //
        };

        std::ostream & operator <<(std::ostream & file, const Cell & me);
        std::istream & operator >>(std::istream & file, Cell & me);
    }
#endif
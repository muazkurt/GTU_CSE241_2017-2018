#ifndef CONNECTFOURPLUS_H
    #define CONNECTFOURPLUS_H 
    #include "./ConnectFourAbstract.h"
    namespace MuazKurt
    {
        class ConnectFourPlus : public ConnectFourAbstract
        {
        public:
            /*
                1 default valued parameter constructer.
            */
            ConnectFourPlus(int square = 5);

            /*
                2 parameter constructer.
            */
            ConnectFourPlus(int rectHeight, int rectWidth);

            /*
                Copy constructer.
            */
            ConnectFourPlus(const ConnectFourPlus & other);

            /*
                Watchs only vertical and horizontal ways for win.
            */
            bool WinSituation();

            /*
                Calls it's own win situation.
            */
            void PlayGame();
        };
    }
#endif
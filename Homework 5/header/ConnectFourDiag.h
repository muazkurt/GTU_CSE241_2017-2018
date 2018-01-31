#ifndef CONNECTFOURDIAG_H
    #define CONNECTFOURDIAG_H 
    #include "./ConnectFourAbstract.h"
    namespace MuazKurt
    {
        class ConnectFourDiag : public ConnectFourAbstract
        {
        public:
            /*
                1 default valued parameter constructer.
            */
            ConnectFourDiag(int square = 5);
            
            /*
                2 parameter constructer.
            */
            ConnectFourDiag(int rectHeight, int rectWidth);
            
            /*
                Copy constructer.
            */
            ConnectFourDiag(const ConnectFourDiag & other);
            
            /*
                Watchs only diagonal ways.
            */
            bool WinSituation();

            /*
                Calls it's own win situation
            */
            void PlayGame();
        };
    }
#endif
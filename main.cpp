#include "inairtable.h"
#include <QApplication>

#include <cstdio>

void usage() {
  printf("\nUSAGE: %s -i tablefile\n", "inairtable.exe");
  printf("\n");
}

int main(int argc, char *argv[])
{

    char *fName="";

    if (argc == 1) {
        usage();
        return (0);
    }
    for(int iArg=0; iArg < argc; iArg++){
        if(iArg < argc-1){
        if( strcmp(argv[iArg],"-i") == 0 || strcmp(argv[iArg],"-table") == 0) {
                iArg++;
                fName = argv[iArg];
        }
        }
        if(strcmp("-help", argv[iArg]) == 0 || strcmp("-h", argv[iArg]) == 0 ) {
         usage();
         return(0);
        }
    }

    QApplication app(argc, argv);
    InAirTable *airTable = new InAirTable;
    airTable->loadData(fName);
    airTable->show();

    return app.exec();
}

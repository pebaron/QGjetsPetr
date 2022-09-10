#include <iostream>
using namespace std;

enum week { Sunday, Monday, Tuesday, Wednesday, Thursday, Friday, Saturday };
enum MetaDataType {
   /// Release that was used to make the file [string]
   productionRelease = 0,
   /// AMI tag used to process the file the last time [string]
   amiTag = 1,
   /// Version of AODFix that was used on the file last [string]
   AODFixVersion = 2,
   /// Version of AODCalib that was used on the file last [string]
   AODCalibVersion = 3,
   /// Data type that's in the file [string]
   dataType = 4,
   /// Geometry version [string]
   geometryVersion = 5,
   /// Conditions version used for simulation/reconstruction [string]
   conditionsTag = 6,
   /// Beam energy [float]
   beamEnergy = 7,
   /// Beam type [string]
   beamType = 8,
   /// Same as mc_channel_number [float]
   mcProcID = 9,
   /// Fast or Full sim [string]
   simFlavour = 10,
   /// Used data overlay for backgrounds [bool]
   isDataOverlay = 11,
   /// End marker
   END = 12
};


//fmd->MetaDataType
int enumerator(){
    MetaDataType today;
    today = isDataOverlay;
    cout << "does not include " << today;

    
    enum Rank { ACE = 1, DEUCE, TREY, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING };
    int m_rank = 0;
    const char* rank_txt[] = {"Ace", "Deuce", "Trey", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Four", "King" } ;
    cout << rank_txt[m_rank - 1] << endl;;

    
    return 0;
}
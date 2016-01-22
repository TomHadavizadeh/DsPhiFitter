// Include files 
#include <stdlib.h>
#include <ostream>
#include <sstream>

// local
#include "Parameters.h"
#include "CommonTools.h"

//-----------------------------------------------------------------------------
// Implementation file for class : Parameters
//
// 2009-06-19 : Malcolm John
//-----------------------------------------------------------------------------

Parameters::Parameters(  )
  : Base()
  , toylocation("NULL")
    //, autolocation("NULL")
  , locationoption("NULL")
    //, variationoption("NULL")
  , locations()
  , moption("NULL")
  , doption("NULL")
  , polarity("both")
  //, toVary("NULL")
  //, toFix("NULL")
  , readToys(false)
  , genToys(false)
  , nToys(0)
  , doDraw(true)
  , doFit(true)
  , sumOverCharges(false)
  , batch(false)
  //, vary(false)
  , binned(false)
  , quickVersion(false)
  , minos(false)
{
  //put variations here
  //variation[kPidEff]=false;	

}

void Parameters::help()
{
  std::cout << "" << std::endl;
  std::cout << "********************************************************************" << std::endl;
  std::cout << " The following options are possible:" << std::endl;
  std::cout << "Options:  " << std::endl;
  std::cout << "    -m <modes> colon-separated list of modes from:" << std::endl;
  std::cout << "                    Ds2KKPi, Ds2PiPiPi, Ds2KPiPi" << std::endl;
  std::cout << "    -t  <N>    do not fit to data, but generate N toys " << std::endl;
  std::cout << "               if no number is specified, the toys are " << std::endl;
  std::cout << "               read from the below location " << std::endl;
  std::cout << "    -a <pol>   magnet polarity choice {both,up,down} default: "<< polarity << std::endl;
  //std::cout << "    -v <type>  vary some quantity according to its error. Choose from:" << std::endl;
  //std::cout << "                 nothing atm... " << std::endl;
  //std::cout << "    -f <str>   colon-separated list of variables to fix in the likelihood scan" << std::endl;
  std::cout << "    -d <dset>  colon-separated list of strippings. Choose from: s21:s21r1" << std::endl;
  std::cout << "Locations:  " << std::endl;
  std::cout << "    -L <dir> colon-separated list of locations." << std::endl;
  std::cout << "             At these locations, program looks for:  " << std::endl;
  std::cout << "             d2kpi.root, d2pik.root, etc." << std::endl;
  std::cout << "    -T <dir> location of toy directory." << std::endl;
  //std::cout << "    -A <dir> location for fit results in automatic mode" << std::endl;
  //std::cout << "    -V <dir> location for fit results in systematics mode" << std::endl;
  std::cout << "Switches:  " << std::endl;
  std::cout << "    -S sum over charges" << std::endl;
  std::cout << "    -B binned fit performed" << std::endl;
  std::cout << "    -0 fit is not performed but pdfs drawn" << std::endl;
  std::cout << "    -N fit not performed, pdfs not drawn" << std::endl;
  std::cout << "    -M run minos" << std::endl;
  std::cout << "    -X batch mode, no X11" << std::endl;
  std::cout << "    -Q quicker version -- if possible, does not read ntuples" << std::endl;
  std::cout << "      (though non-quick version needed first to make ntuples)" <<std::endl;
  std::cout << "********************************************************************" << std::endl;
  std::cout << "Typical executions are:" << std::endl;
  std::cout << " ~> bin/run -m d2kpi:d2kk:d2pipi -L ~/DATA -a up" << std::endl;
  std::cout << " ~> bin/run -m d2kpi:d2pik -Q -p 8" << std::endl;
  std::cout << " ~> bin/run -m d2kpi -T ~/TOYS -t 10" << std::endl;
  std::cout << " ~> bin/run -m d2kpi -T ~/TOYS -t" << std::endl;
  std::cout << "" << std::endl;
}

int Parameters::readCommandLine(unsigned int narg, char *argv[])
{
  bool OK=true;
  unsigned int i=1;

  if(narg==1){
    help();
    return 1;
  }

  std::string task;

  while(argv[i++])
  {
    std::string s(argv[i-1]);
    if(int(s[0])==int('-')){
      switch(int(s[1])){
			case int('0'):
				doFit=false;
				break;
			case int('N'):
				doFit=false;
				doDraw=false;
        break;
      case int('M'):
        minos=true;
        break;
      case int('B'):
        binned=true;
        break;
			case int('X'):
				batch=true;
        break;
      case int('Q'):
      	quickVersion=true;
        break;
      case int('S'):
        sumOverCharges=true;
        break;
	//case int('v'):
        //if(i==narg){OK=false;break;}if(int(argv[i][0])==int('-')){OK=false;break;}i++;//always needed if option takes an argument
        //toVary=std::string(argv[i-1]);
        //break;
	//case int('f'):
        //if(i==narg){OK=false;break;}if(int(argv[i][0])==int('-')){OK=false;break;}i++;//always needed if option takes an argument
        //toFix=std::string(argv[i-1]);
        //break;
      case int('a'):
      	if(i==narg){OK=false;break;}if(int(argv[i][0])==int('-')){OK=false;break;}i++;//always needed if option takes an argument
	polarity=std::string(argv[i-1]);
        break;
	//case int('V'):
        //if(i==narg){OK=false;break;}if(int(argv[i][0])==int('-')){OK=false;break;}i++;//always needed if option takes an argument
        //variationoption=std::string(argv[i-1]);
        //batch=true;
        //break;
	//case int('A'):
        //automatic=true;
        //if(i==narg){OK=false;break;}if(int(argv[i][0])==int('-')){OK=false;break;}i++;//always needed if option takes an argument
        //autolocation=std::string(argv[i-1]);
        //batch=true;
        //break;
      case int('T'):
	if(i==narg){OK=false;break;}if(int(argv[i][0])==int('-')){OK=false;break;}i++;//always needed if option takes an argument
	toylocation=std::string(argv[i-1]);
      	break;
      case int('L'):
       	if(i==narg){OK=false;break;}if(int(argv[i][0])==int('-')){OK=false;break;}i++;//always needed if option takes an argument
     	locationoption=std::string(argv[i-1]);
        break;
      case int('d'):
        if(i==narg){OK=false;break;}if(int(argv[i][0])==int('-')){OK=false;break;}i++;//always needed if option takes an argument
        doption=std::string(argv[i-1]);
        break;
      case int('m'):
        if(i==narg){OK=false;break;}if(int(argv[i][0])==int('-')){OK=false;break;}i++;//always needed if option takes an argument
        moption=std::string(argv[i-1]);
        break;
      case int('t'):
       	if(i==narg){readToys=true;break;}if(int(argv[i][0])==int('-')){readToys=true;break;}i++;//if option sometimes takes an argument
	nToys=atoi(argv[i-1]);
	genToys=true;
	break;
       	
      default:
        std::cout << " Don't recognise option '"<< s <<"'" << std::endl;
        OK=false;
      }
    }else{
      std::cout << " Don't recognise argument '"<< s <<"'" << std::endl;
      OK=false;
    }
  }

  std::vector<std::string> tokens;
	if(moption==null){
		std::cout << " At least one mode must be specified with -m <mode>" << std::endl;
		OK=false;
	}else{
		CommonTools::split(moption, tokens, ":");
		for(unsigned int i=0;i<tokens.size();i++){
			modes[tokens[i]]=true;
			if(tokens[i]!=Ds2KKPi && tokens[i]!=Ds2PiPiPi && tokens[i]!=Ds2KPiPi){
				std::cout << " Don't recognise mode: " << tokens[i] << std::endl;
				OK=false;
			}
		}
	}
	//if(modes[d2pik]    &&not modes[d2kpi]){    std::cout << " Can't fit pik without kpi."         << std::endl; OK=false;}


  
  
	if(locationoption==null){
		if(!genToys&&!readToys&&!quickVersion){
			std::cout << " The location -L not specified. Generating data from the model." << std::endl;
      genToys=true;
      nToys=1;
		}
	}else{
    std::vector<std::string> tokens;
    CommonTools::split(locationoption, tokens, ":");
    for(unsigned int i=0;i<tokens.size();i++){
      locations.push_back(tokens[i]);
    }
  }
	if(genToys||readToys){
		if(toylocation==null&&nToys>1){
			std::cout << " The location of the final ntuples must be specified with the -T <location> option." << std::endl;
		  OK=false;
		}
		if(toylocation!=null&&nToys==1){
			std::cout << " Does not make sense to specify toy location when running one toy (which is not stored)" << std::endl;
		  OK=false;
		}
		if(locationoption!=null&&nToys==1){
			std::cout << " Does not make sense to specify data(!) location when doing toys" << std::endl;
		  OK=false;
		}
		//if(automatic){
		//std::cout << " Incompatible options: -A and -T" << std::endl;
		//OK=false;
		//}
	}
  if(genToys&&nToys>1){
  	batch=true;
  }
  //if(automatic&&autolocation==null){
  //  std::cout << " -A <location> not complete" << std::endl;
  //  OK=false;
  //}
  
	if(batch){
		std::cout << "Set to batch mode!"<< std::endl;
	}
	
	//if(toVary!=null){
	  //vary=true;
  	  //bool understood=false;
  	  //for(std::map<std::string,bool>::iterator mi=variation.begin();mi!=variation.end();mi++){
    	    //if((*mi).first==toVary){
	      //(*mi).second=true;
            //understood=true;
            //break;
	    //}
	    //}
          //if(!understood){
	    //std::cout<<"Don't understand quantity to vary: '"<< toVary <<"'"<<std::endl;
    	  //OK=false;
          //}
          //if(variationoption==null){
	    //std::cout<<"Must specify fit result storage location with -V <someplace>"<<std::endl;
    	  //OK=false;
          //}
	  //}else{
          //if(variationoption!=null){
	    //std::cout<<"Does not make sense to have -V option without -v"<<std::endl;
	  // OK=false;
	  //  }
	  //} //end of else (from toVary)
  	
	if(polarity!=std::string("sensitive")&&polarity!=std::string("both")&&polarity!=std::string("up")&&polarity!=std::string("down")&&polarity!=std::string("dn")){
		std::cout << "Don't recognise -M option \""<<polarity<<"\" {both,up,down}"<< std::endl;
		OK=false;
	}else if(polarity==std::string("down")){
		polarity=std::string("dn");
	}


  if(not genToys){
    tokens.clear();
    if(doption==null){
      std::cout << "Dataset unspecified (-d <dset>)." << std::endl;
      OK=false;
    }
    CommonTools::split(doption, tokens, ":");
    for(unsigned int i=0;i<tokens.size();i++){
      dsetsReq[tokens[i]]=true;
      if(tokens[i]!=s21 && tokens[i]!=s21r1){
        std::cout << " Don't recognise dataset '" << tokens[i] << "'. Expect s21:s21r1" << std::endl;
        OK=false;
      }
      std::map<std::string,bool> tmp;
      //for(std::map<std::string,bool>::iterator mi=variation.begin();mi!=variation.end();mi++){
      //  tmp[(*mi).first]=false;
      //}
      dsetsFound[tokens[i]]=tmp; //not clear what's supposed to happen here if there's no variation asked for...
    }
  }

  
  if(!OK){
    help();
    return 1;
  }

  return 0;
}
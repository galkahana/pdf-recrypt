#include <iostream>
#include <string>

#include "BoxingBase.h"
#include "PDFWriter.h"

using namespace std;
using namespace PDFHummus;

static void ShowUsage(const string& name)
{
    cerr << "Usage: " << name << " inputfilepath outputfilepath <option(s)>\n"
            << "inputfilepath - input pdf file path\n"
            << "outputfilepath - output pdf file path\n"
            << "Options:\n"
            << "\t-p, --password password\t\tInput pdf password (user or owner). Default is no password\n"
            << "\t-v, --version <d>\t\tOutput pdf version. Use 10-17 for pdf1.0-pdf1.7. For AES use 16 or 17. Lower is RC4. Default is input pdf version\n"
            << "\t-u, --user-password password\tOutput pdf password (user password). Default is no password\n"
            << "\t-o, --owner-password password\tOutput pdf owner password. Default is no owner password password\n"
            << "\t-f, --user-protection-flag <d>\tOutput pdf user protection flag. Default is 4 (low res print)\n"            
            << "\t-h, --help\t\t\tShow this help message\n"
            << endl;
}

typedef BoxingBaseWithRW<long long> LongLong;

int main(int argc, char* argv[])
{
    if(argc < 3) {
        ShowUsage(argv[0]);
        return 1;        
    }

    string inputFilePath = argv[1];
    string outputFilePath = argv[2];
    EPDFVersion outputFileVersion = ePDFVersionUndefined;
    string inputFilePassword = "";
    bool shouldEncrypt = false;
    string outputFilePassword = "";
    string outputFileOwnerPassword = "";
    long long userProtectionFlag = 4;


    for (int i = 3; i < argc; ++i) {
        std::string arg = argv[i];
        if ((arg == "-h") || (arg == "--help")) {
            ShowUsage(argv[0]);
            return 0;
        } else if ((arg == "-p") || (arg == "--password")) {
            if(i + 1 < argc) {
                inputFilePassword = argv[++i];
            } else {
                std::cerr << "--password option requires one argument to specify the input file password" << std::endl;
                return 1;
            }
        } else if ((arg == "-v") || (arg == "--version")) {
            if(i + 1 < argc) {
                int argInt = Int(argv[++i]);
                if(argInt >= 10 && argInt <=17) {
                    outputFileVersion = EPDFVersion(argInt);
                }
                else {
                    std::cerr << "--version option requires one numeral argument to the output file version. Use 10 to 17 for PDF1.0 to PDF1.7." << std::endl;
                    return 1;
                }
            } else {
                std::cerr << "--version option requires one numeral argument to the output file version. Use 10 to 17 for PDF1.0 to PDF1.7." << std::endl;
                return 1;
            }
        } else if ((arg == "-u") || (arg == "--user-password")) {
            if(i + 1 < argc) {
                outputFilePassword = argv[++i];
            } else {
                std::cerr << "--user-password option requires one argument to specify the output file password" << std::endl;
                return 1;
            }
        } else if ((arg == "-o") || (arg == "--owner-password")) {
            if(i + 1 < argc) {
                outputFileOwnerPassword = argv[++i];
            } else {
                std::cerr << "--owner-password option requires one argument to specify the output file owner password" << std::endl;
                return 1;
            }
        } else if ((arg == "-f") || (arg == "--user-protection-flag")) {
            if(i + 1 < argc) {
                long long argLongLong = LongLong(argv[++i]);
                if(argLongLong >= 0) {
                    userProtectionFlag = argLongLong;
                }
                else {
                    std::cerr << "--user-protection-flag option requires one integer argument (bitwise flag) to specify the output file user protection flag" << std::endl;
                    return 1;
                }
            } else {
                std::cerr << "--user-protection-flag option requires one integer argument (bitwise flag) to specify the output file user protection flag" << std::endl;
                return 1;
            }
        } else {
            cerr << "Unrecognized option " << arg << std::endl;
            ShowUsage(argv[0]);
            return 1;
        }
    }

    EStatusCode status = PDFWriter::RecryptPDF(
                            inputFilePath, 
                            inputFilePassword, 
                            outputFilePath, 
                            LogConfiguration::DefaultLogConfiguration(), 
                            PDFCreationSettings(
                                true, 
                                true, 
                                EncryptionOptions(
                                    outputFilePassword.size()>0 || outputFileOwnerPassword.size()>0, 
                                    outputFilePassword, 
                                    userProtectionFlag, 
                                    outputFileOwnerPassword
                                )
                            )
                        );

    return status == eSuccess ? 0:1;
}
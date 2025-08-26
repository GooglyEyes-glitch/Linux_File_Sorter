#include <iostream> 
#include <filesystem>

namespace fs = std::filesystem;
	
struct ScanEval{

	bool Downloads = false;
	bool Pictures = false;
	bool Videos = false;
	bool Documents = false;
	fs::path scan_path;
};

void display_dir_status(ScanEval &scan){
	
	std::cout << "-------------Directory-Status------------" << std::endl;
	std::cout << "[/] If dir exists value = 1 else value = 0" << std::endl;
	std::cout << "[/] Downloads: " << scan.Downloads << std::endl;
	std::cout << "[/] Pictures: " << scan.Pictures << std::endl;
	std::cout << "[/] Videos: " << scan.Videos << std::endl;
	std::cout << "[/] Documents: " <<  scan.Documents << std::endl;
	std::cout << "[/] Current path being used: " << scan.scan_path << std::endl;
}

// This checks if the listed folders in the struct ScanEval exists, if they do exist then there value will be changed from 0 to 1
void update_dir_status(ScanEval &scan){
	
	std::cout << "----Updating-Directory-Status----" << std::endl;

	if(fs::exists(scan.scan_path)){	

		scan.Downloads = fs::exists(scan.scan_path / "Downloads");
		scan.Pictures = fs::exists(scan.scan_path / "Pictures" );
		scan.Videos = fs::exists(scan.scan_path / "Videos" );
		scan.Documents = fs::exists(scan.scan_path / "Documents");

		std::cout << "[/] Successfully updated diretory status" << std::endl;
	}

	else{
		std::cout << "[-] Failed to find directory path, please make sure its correct or has been set. " << std::endl;
	}
}

void display_directory_contents(ScanEval &scan){

	std::cout << "--------Directory-Contents---------------" << std::endl;
	for(const auto &x : fs::directory_iterator(scan.scan_path)){

		std::cout << x.path() << '\n';
	}
}

void help_menu(){
	std::cout << "[/] To exit the program enter '0' " << std::endl;
	std::cout << "[/] To view directory status enter '1' " << std::endl;
	std::cout << "[/] To setup scan setting enter '2' " << std::endl;
	std::cout << "[/] To update directory status press 3, only after a path is selected with '2' " << std::endl;
	std::cout << "[/] To scan target directory press '4' " << std::endl;
}

void get_scan_settings(ScanEval &scan){
	
	std::cout << "---------Pre-Scan-Setup--------------" << std::endl;
	while (true){
		
		std::cout << "Enter the path to the target directory, example /home/user/Downloads" << std::endl;
		std::cout << "[+] input: ";
		std::cin >> scan.scan_path;

		if(!fs::exists(scan.scan_path)){
			std::cout << "[-] Unable to access directory: " << scan.scan_path << std::endl;
			continue;
		}
		
		else{
			std::cout << "[/] Path: " << scan.scan_path << " was found" << std::endl;
			return;
		}
	}
}

void main_menu(){
	
	ScanEval scan;
	int input = 0;

	while (true){
		
		std::cout << "------Main-Menu------" << std::endl;
		help_menu();

		std::cout << "[+] Input: ";
		std::cin >> input;

		switch(input){
			
			case 0:
				return;
			
			case 1:
				display_dir_status(scan);
				break;
			
			case 2:
				get_scan_settings(scan);
				break;

			case 3:
				update_dir_status(scan);
				break;

			case 4:
				display_directory_contents(scan);
				break;

			default:
				std::cout << "[-] Invalid Input " << std::endl;
				break;
		}
	}
}


int main(){
	main_menu();
	return 0;
}

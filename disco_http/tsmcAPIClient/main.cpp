#include "tsmcAPIClient.h"

#define IMG_1 "test.csv"
#define IMG_2 "test.csv"

const std::string command = "Disco test";

void client_no_config_test(tsmcAPIClient &client);
StatusCode bmp_test(tsmcAPIClient &client, std::string img_path_1, std::string img_path_2);
std::string TEST_IMG_PATH = "C:\\Users\\sandbox\\Desktop\\disco_http\\csv_file\\";

int main(int argc, char* argv[]) {
    std::wstring iniPath = L".\\config.ini";
    std::string result;
    StatusCode ret = TSMC_OK;
    Config config;
    tsmcAPIClient client;

    if (argc > 1){
        TEST_IMG_PATH = argv[1];
    }
    std::cout << TEST_IMG_PATH << std::endl;
    ret = client.init(iniPath);
    std::wcout << L"Version: " << client.GetVersion() << std::endl << std::endl;

    if (ret > 0){
        std::cerr << "client init error : " << ret << std::endl;
        return 1;
    }

    // Bmp test
    if ((ret = bmp_test(client, IMG_1, IMG_2))!= TSMC_OK){
        std::cerr << "Bmp test failed. Code: " << ret << std::endl;
    }else{
        std::cout << "Bmp test pass." << std::endl;
    }


	system("pause");
    return 0;
}

StatusCode bmp_test(tsmcAPIClient &client, std::string img_path_1, std::string img_path_2){
    std::string result;
    std::string path1 = TEST_IMG_PATH + img_path_1;
    std::string path2 = TEST_IMG_PATH + img_path_2;
    std::vector<BYTE> bitmap1, bitmap2;

    if (!LoadBmpToVector(path1.c_str(), bitmap1) || !LoadBmpToVector(path2.c_str(), bitmap2)) {
        return TSMC_BITMAP_FAILED;
    }

    StatusCode ret = client.AOIApi(command, bitmap1, bitmap2, result);
    return ret;
}
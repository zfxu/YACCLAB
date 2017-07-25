#ifndef YACCLAB_CONFIG_DATA_H_
#define YACCLAB_CONFIG_DATA_H_

#include <opencv2/imgproc.hpp>

#include "file_manager.h"
#include "utilities.h"

using namespace filesystem;

struct ConfigData {

	bool perform_check_8connectivity;	// Whether to perform 8-connettivity check or not
	bool perform_check_4connectivity;  // Whether to perform 8-connettivity check or not (not used and set yet)

	bool perform_average;				// Whether to perform average tests or not
	bool perform_density;				// Whether to perform density tests or not
	bool perform_memory;				// Whether to perform memory tests or not
	bool perform_average_ws;			// Whether to perform average tests with steps or not

	bool average_color_labels;			// If active, labeled image from average tests will be colored and stored
	bool density_color_labels;			// If active, labeled image from density tests will be colored and stored
	bool write_n_labels;				// If active, the number of components generated by the algorithms will be stored in the output file
	bool average_save_middle_tests;		// If active, results of each average test run will be stored 
	bool density_save_middle_tests;		// If active, results of each density test run will be stored 
    bool average_ws_save_middle_tests;   // If active, results of each average test with steps run will be stored 

	unsigned average_tests_number;		// Reps of average tests (only the minimum will be considered)
	unsigned density_tests_number;		// Reps of density tests (only the minimum will be considered)
	unsigned average_ws_tests_number;	// Reps of average tests with steps (only the minimum will be considered)

	std::string input_txt;					// File of images list
	std::string gnuplot_script_extension;	// Gnuplot scripts extension
	std::string colors_folder;				// Folder which will store colored images
	std::string middle_folder;				// Folder which will store middle results
	std::string latex_file;					// Latex file which will store textual average results
	std::string latex_memory_file;			// Latex file which will store textual memory results
	std::string latex_charts;				// Latex file which will store report latex code for charts
	path output_path;						// Path on which results are stored
	path input_path;						// Path on which input datasets are stored
	path latex_path;						// Path on which latex report will be stored

	std::vector<cv::String> check_datasets;		// List of datasets on which check tests will be performed
	std::vector<cv::String> memory_datasets;	// List of datasets on which memory tests will be perform
	std::vector<cv::String> density_datasets;	// List of datasets on which density tests will be performed
    std::vector<cv::String> average_datasets;	// Lists of dataset on which averages tests will be performed
    std::vector<cv::String> average_datasets_ws;// Lists of dataset on which averages tests whit steps will be performed

	std::vector<cv::String> ccl_algorithms;		// Lists of 'STANDARD' algorithms to check and/or test

	ConfigData(const cv::FileStorage& fs) {
		// Flags to customize output format (false by default)
		perform_check_8connectivity = ReadBool(fs["perform"]["check_8connectivity"]);
		perform_average				= ReadBool(fs["perform"]["average"]);
		perform_density				= ReadBool(fs["perform"]["density"]);
		perform_memory				= ReadBool(fs["perform"]["memory"]);
		perform_average_ws			= ReadBool(fs["perform"]["average_with_steps"]);

		average_color_labels		= ReadBool(fs["color_labels"]["average"]);
		density_color_labels		= ReadBool(fs["color_labels"]["density"]);
		
		write_n_labels				= ReadBool(fs["write_n_labels"]);
		
		average_save_middle_tests	= ReadBool(fs["save_middle_tests"]["average"]);
		density_save_middle_tests	= ReadBool(fs["save_middle_tests"]["density"]);
		average_ws_save_middle_tests	= ReadBool(fs["save_middle_tests"]["average_with_steps"]);

		average_tests_number		= static_cast<int>(fs["tests_number"]["average"]);
		density_tests_number		= static_cast<int>(fs["tests_number"]["density"]);
		average_ws_tests_number		= static_cast<int>(fs["tests_number"]["average_with_steps"]);

		input_txt					= "files.txt";
		gnuplot_script_extension	= ".gnuplot";
		colors_folder				= "colors";
		middle_folder				= "middle_results";
		latex_file					= "averageResults.tex";
		latex_charts				= "averageCharts.tex";
		latex_memory_file			= "memoryAccesses.tex";
		
        output_path                 = path(fs["paths"]["output"]) / path(GetDatetimeWithoutSpecialChars());
		input_path					= path(fs["paths"]["input"]);
		latex_path					= output_path / path("latex");

		check_datasets				= std::vector<cv::String>(fs["check_datasets"].size());
		cv::read(fs["check_datasets"], check_datasets);
		
		memory_datasets				= std::vector<cv::String>(fs["memory_datasets"].size());
		cv::read(fs["memory_datasets"], memory_datasets);
		
		density_datasets			= std::vector<cv::String>(1, { "test_random" });
		
		average_datasets			= std::vector<cv::String>(fs["average_datasets"].size());
		cv::read(fs["average_datasets"], average_datasets);

        average_datasets_ws = std::vector<cv::String>(fs["average_datasets_with_steps"].size());
        cv::read(fs["average_datasets_with_steps"], average_datasets_ws);

		ccl_algorithms				= std::vector<cv::String>(fs["algorithms"].size());
		cv::read(fs["algorithms"], ccl_algorithms);
	}

	bool ReadBool(const cv::FileNode& node_list)
	{
		bool b = false;
		if (!node_list.empty()) {
			//The entry is found
			std::string s((std::string)node_list);
			std::transform(s.begin(), s.end(), s.begin(), ::tolower);
			std::istringstream(s) >> std::boolalpha >> b;
		}
		return b;
	}
};

#endif // !YACCLAB_CONFIG_DATA_H_

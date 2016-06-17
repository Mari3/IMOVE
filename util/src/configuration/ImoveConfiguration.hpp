#ifndef IMOVECONFIGURATION_H
#define IMOVECONFIGURATION_H

#include "CameraConfiguration.hpp"
#include "ProjectorConfiguration.hpp"
#include "ProjectioneliminationConfiguration.hpp"

// Class for reading configuration from yml file
class ImoveConfiguration {
	public:
		static const bool DEFAULT_DEBUG_MODE = true;
		
		/**
		 * Setup properties for configuration.
		 *
		 * @param debug_mode                          The debug mode
		 * @param camera_configuration                The configuration for the camera
		 * @param projector_configuration             The configuration for the projector
		 * @param projectionelimination_configuration The configuration for the projection elimination
		 **/
		ImoveConfiguration(const bool debug_mode, CameraConfiguration* camera_configuration, ProjectorConfiguration* projector_configuration, ProjectioneliminationConfiguration* projectionelimination_configuration);

		/**
		 * Creates the ImoveConfiguration from a file by which the filepath is given
		 *
		 * @param filepath Path to file from which to read ImoveConfiguration
		 **/
		static ImoveConfiguration* readFile(const char* filepath);

		/**
		 * Creates the ImoveConfiguration from a file by which the filepath is given and defaults
		 *
		 * @param filepath Path to file from which to load ImoveConfiguration
		 **/
		static ImoveConfiguration* createFromFile(const char* filepath, const int deviceid_camera, const cv::Size& resolution_projector);

		/**
		 * Creates the file by which the filepath is given from the ImoveConfiguration
		 *
		 * @param filepath Path to file to which to save ImoveConfiguration
		 **/
		void writeFile(const char* filepath) const;

		/**
		 * Derive the projection meter from camera meter
		 **/
		void deriveMeterProjectorFromMeterCamera();

		/**
		 * Derive the camera projector transformation
		 **/
		void deriveCameraProjectorTransformation();

		/**
		 * Gets the camera projector transformation
		 **/
		const cv::Mat getCameraProjectorTransformation();

		/**
		 * Gets debug mode 
		 **/
		const bool getDebugMode() const;
		
		/**
		 * Get the camera configuration
		 **/
		CameraConfiguration* getCameraConfiguration() const;

		/**
		 * Get the projector configuration
		 **/
		ProjectorConfiguration* getProjectorConfiguration() const;

		/**
		 * Get the projection elimination configuration
		 **/
		ProjectioneliminationConfiguration* getProjectioneliminationConfiguration() const;

	protected:
		const bool debug_mode;
		CameraConfiguration* camera_configuration;
		ProjectorConfiguration* projector_configuration;
		ProjectioneliminationConfiguration* projectionelimination_configuration;

		cv::Mat camera_projector_transformation;
};

#endif // IMOVECONFIGURATION_H

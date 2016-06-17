#ifndef PROJECTORCONFIGURATION_H
#define PROJECTORCONFIGURATION_H

#include <opencv2/imgproc/imgproc.hpp>
#include "Configuration.hpp"

// Configuration to store variales for projector configuration
class ProjectorConfiguration : public Configuration {
	public:
		// Default configuration parameters if not given when createFromNode
		static constexpr unsigned int  DEFAULT_MAXIMUM_FPS_SCENE = 60;
		static constexpr          bool DEFAULT_FULLSCREEN        = true;
		static constexpr          bool DEFAULT_METER             = 100;
		
		/**
		 * Setup properties for mapping projector from camera.
		 * 
		 * @param resolution_projector The projector resolution
		 * @param fullscreen_projector The projector fullscreen or not
		 * @param meter The amount of pixels measured as 1 meter on projector frame
		 * @param maximum_fps_scene The maximum fps for the scene
		 **/
		ProjectorConfiguration(const cv::Size& resolution_projector, const bool& fullscreen_projector, float meter, unsigned int maximum_fps_scene);

		/**
		 * Creates the ProjectorConfiguration from a file node by which the filepath is given
		 * 
		 * @param read_config File node from which to read ProjectorConfiguration
		 **/
		static ProjectorConfiguration* readNode(cv::FileStorage read_config);
		
		/**
		 * Creates the ProjectorConfiguration from a file node from which the filepath is given and defaults
		 * 
		 * @param read_config File node from which to load ProjectorConfiguration
		 * @param resolution The resolution of the projector
		 **/
		static ProjectorConfiguration* createFromNode(cv::FileStorage read_config, cv::Size resolution);
		
		/**
		 * Creates the file by which the file node is given from the ProjectorConfiguration
		 * 
		 * @param write_config File node to which to save ProjectorConfiguration
		 **/
		void writeNode(cv::FileStorage write_config) const;

		/**
		 * Gets the resolution of the projector.
		 **/
		const cv::Size getResolution() const;

		/**
		 * Gets whether the scene should be fullscreen on projector.
		 **/
		bool getFullscreen() const;
		
		/**
		 * Sets the one meter in pixels on a projector image.
		 **/
		void setMeter(float meter);
		
		/**
		 * Gets the one meter in pixels on a projector image.
		 **/
		const float getMeter() const;

		/**
		 * Sets the maximum FPS of the scene
		 * 
		 * @param maximum_fps_scene The maximum amount of frames per second for the scene
		 **/
		void setMaximumFpsScene(const unsigned int maximum_fps_scene);

		/**
		 * Gets the maximum frames per second of the scene
		 **/
		const unsigned int getMaximumFpsScene() const;

	protected:
		// The projector resolution
		cv::Size resolution;
		// Whether to put scene fullscreen or not
		bool fullscreen;
		// 1 meter in pixels on projector image
		float meter;
		// fps scene
		unsigned int maximum_fps_scene;
};

#endif // PROJECTORCONFIGURATION_H

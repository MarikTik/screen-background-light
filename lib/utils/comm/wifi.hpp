/**
 * @file wifi.hpp
 * @brief Provides a simple interface for initializing and managing WiFi connections on the ESP32.
 *
 * This header defines the `wifi` class, which encapsulates functionality for:
 * - Connecting to a WiFi network with an SSID and password.
 * - Setting up mDNS for device discovery with a specified hostname.
 * - Managing updates to the WiFi connection (future functionality).
 *
 * @note This library is designed for use with ESP32 devices and leverages the ESP32-specific WiFi and mDNS libraries.
 */
#ifndef WIFI_HPP_
#define WIFI_HPP_

namespace comm{
     /**
     * @class wifi
     * @brief Encapsulates functionality for managing WiFi connections on the ESP32.
     *
     * The `wifi` class provides an easy-to-use interface for connecting an ESP32 to a WiFi network,
     * initializing mDNS for hostname-based discovery, and handling WiFi updates.
     */
     class wifi{
     public:
         /**
         * @brief Constructs a `wifi` instance with the specified WiFi credentials and hostname.
         * @note If no hostname is provided, mDNS will not be set up.
         * @param ssid The SSID of the WiFi network to connect to.
         * @param password The password for the WiFi network.
         * @param hostname The hostname for mDNS discovery, Defaults to empty string.
         */
          wifi(const char* ssid, const char* password, const char* hostname = "");

          /**
          * @brief Begins the WiFi connection process and sets up mDNS.
          *
          * This method:
          * - Connects to the WiFi network using the provided SSID and password.
          * - Waits for the connection to be established.
          * - Configures mDNS with the provided hostname.
          *
          * @note This function blocks execution until the WiFi connection is established.
          */
          void begin();

          /**
          * @brief Updates the WiFi connection status.
          *
          * This method is intended to handle periodic updates or checks related to the WiFi connection.
          * Currently, it is a placeholder for future functionality.
          */
          void update();

     private:
          const char* _ssid;       ///< The SSID of the WiFi network.
          const char* _password;   ///< The password for the WiFi network.
          const char* _hostname;   ///< The hostname for mDNS discovery.
     };

} // namespace comm

#endif // WIFI_HPP_
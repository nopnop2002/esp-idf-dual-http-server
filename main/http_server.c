/*	Simple HTTP Server Example

	This example code is in the Public Domain (or CC0 licensed, at your option.)

	Unless required by applicable law or agreed to in writing, this
	software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
	CONDITIONS OF ANY KIND, either express or implied.
*/

#include <stdio.h>
#include <inttypes.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/message_buffer.h"
#include "esp_log.h"
#include "esp_http_server.h"
#include "cJSON.h"

#include "parameter.h"

extern MessageBufferHandle_t xMessageBufferSta;
extern MessageBufferHandle_t xMessageBufferEth;

/* root get handler */
static esp_err_t root_get_handler(httpd_req_t *req)
{
	ESP_LOGI(__FUNCTION__, "req->content_len=%d", req->content_len);
	ESP_LOGI(__FUNCTION__, "req->user_ctx=[%s]", req->user_ctx);

	/* Send response */
	httpd_resp_sendstr_chunk(req, "Hello ");
	httpd_resp_sendstr_chunk(req, req->user_ctx);

	/* Send empty chunk to signal HTTP response completion */
	httpd_resp_sendstr_chunk(req, NULL);
	return ESP_OK;
}

/* json get handler */
static esp_err_t json_get_handler(httpd_req_t *req)
{
	ESP_LOGI(__FUNCTION__, "req->content_len=%d", req->content_len);
	ESP_LOGI(__FUNCTION__, "req->user_ctx=[%s]", req->user_ctx);

	/* Send response */
	cJSON *root;
	root = cJSON_CreateObject();
	cJSON_AddStringToObject(root, "interface", req->user_ctx);
	char *my_json_string = cJSON_Print(root);
	//char *my_json_string = cJSON_PrintUnformatted(root);
	ESP_LOGI(__FUNCTION__, "my_json_string\n%s",my_json_string);
	cJSON_Delete(root);
	httpd_resp_sendstr_chunk(req, my_json_string);
	cJSON_free(my_json_string);

	/* Send empty chunk to signal HTTP response completion */
	httpd_resp_sendstr_chunk(req, NULL);
	return ESP_OK;
}


/* root post handler */
static esp_err_t root_post_handler(httpd_req_t *req)
{
	ESP_LOGI(__FUNCTION__, "req->content_len=%d", req->content_len);
	ESP_LOGI(__FUNCTION__, "req->user_ctx=[%s]", req->user_ctx);

	/* Allocate memory */
	char *buf = NULL;
	buf = malloc(req->content_len);
	if (buf == NULL) {
		ESP_LOGE(__FUNCTION__, "malloc fail. req->content_len=%d", req->content_len);
		return ESP_FAIL;
	}

	/* Read the data for the request */
	if (httpd_req_recv(req, buf, req->content_len) != req->content_len) {
		ESP_LOGE(__FUNCTION__, "httpd_req_recv fail");
		free(buf);
		return ESP_FAIL;
	}

	/* Log data received */
	ESP_LOGI(__FUNCTION__, "=========== RECEIVED DATA ==========");
	ESP_LOGI(__FUNCTION__, "%.*s", req->content_len, buf);
	ESP_LOGI(__FUNCTION__, "====================================");
	MessageBufferHandle_t xMessageBuffer = NULL;
	if (strcmp(req->user_ctx, "WiFi") == 0) xMessageBuffer = xMessageBufferSta;
	if (strcmp(req->user_ctx, "Ethernet") == 0) xMessageBuffer = xMessageBufferEth;
	size_t sended = xMessageBufferSend(xMessageBuffer, buf, req->content_len, portMAX_DELAY);
	if (sended != req->content_len) {
		ESP_LOGE(__FUNCTION__, "xMessageBufferSend fail. sended=%d req->content_len=%d", sended, req->content_len);
	}
	free(buf);

	/* Send response */
	httpd_resp_sendstr_chunk(req, "OK");

	/* Send empty chunk to signal HTTP response completion */
	httpd_resp_sendstr_chunk(req, NULL);
	return ESP_OK;
}

/* favicon get handler */
static esp_err_t favicon_get_handler(httpd_req_t *req)
{
	ESP_LOGI(__FUNCTION__, "favicon_get_handler");
	return ESP_OK;
}

/* Function to start the web server */
esp_err_t start_server(int server_port, int ctrl_port, char *user_ctx)
{
	httpd_handle_t server = NULL;
	httpd_config_t config = HTTPD_DEFAULT_CONFIG();
	ESP_LOGD(pcTaskGetName(NULL), "ESP_HTTPD_DEF_CTRL_PORT=%d", ESP_HTTPD_DEF_CTRL_PORT);

	// Purge“"Least Recently Used” connection
	config.lru_purge_enable = true;
	// TCP Port number for receiving and transmitting HTTP traffic
	config.server_port = server_port;
	// UDP Port number for asynchronously exchanging control signals between various components of the server
	config.ctrl_port = ctrl_port;

	// Start the httpd server
	ESP_LOGD(pcTaskGetName(NULL), "httpd_start");
	if (httpd_start(&server, &config) != ESP_OK) {
		ESP_LOGE(pcTaskGetName(NULL), "Failed to start file server!");
		return ESP_FAIL;
	}

	// Set URI handlers
	httpd_uri_t _root_get_handler = {
		.uri = "/",
		.method = HTTP_GET,
		.handler = root_get_handler,
		.user_ctx = user_ctx
	};
	httpd_register_uri_handler(server, &_root_get_handler);

	httpd_uri_t _json_get_handler = {
		.uri = "/json",
		.method = HTTP_GET,
		.handler = json_get_handler,
		.user_ctx = user_ctx
	};
	httpd_register_uri_handler(server, &_json_get_handler);

	httpd_uri_t _root_post_handler = {
		.uri = "/post",
		.method = HTTP_POST,
		.handler = root_post_handler,
		.user_ctx = user_ctx
	};
	httpd_register_uri_handler(server, &_root_post_handler);

	httpd_uri_t _favicon_get_handler = {
		.uri = "/favicon.ico",
		.method = HTTP_GET,
		.handler = favicon_get_handler,
	};
	httpd_register_uri_handler(server, &_favicon_get_handler);

	return ESP_OK;
}

void http_server(void *pvParameters)
{
	PARAMETER_t *task_parameter = pvParameters;
	PARAMETER_t param;
	memcpy((char *)&param, task_parameter, sizeof(PARAMETER_t));
	ESP_LOGI(pcTaskGetName(NULL), "Start");
	ESP_LOGI(pcTaskGetName(NULL), "param.ip=[%s]", param.ip);
	ESP_LOGI(pcTaskGetName(NULL), "param.server.port=[%d]", param.server_port);
	ESP_LOGI(pcTaskGetName(NULL), "param.ctrl_port=[%d]", param.ctrl_port);
	ESP_LOGI(pcTaskGetName(NULL), "param.user_ctx=[%s]", param.user_ctx);
	char url[64];
	sprintf(url, "http://%s:%d", param.ip, param.server_port);
	ESP_LOGI(pcTaskGetName(NULL), "Starting HTTP server on %s", url);
	ESP_ERROR_CHECK(start_server(param.server_port, param.ctrl_port, param.user_ctx));

	while(1) {
		vTaskDelay(1);
	}

	// Never reach here
	ESP_LOGI(pcTaskGetName(NULL), "finish");
	vTaskDelete(NULL);
}

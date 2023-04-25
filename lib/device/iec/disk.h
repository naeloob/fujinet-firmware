#ifndef DISK_H
#define DISK_H

#include "fujiHost.h"

#include <string>
#include <unordered_map>

#include "bus.h"
#include "media.h"
#include "meat_io.h"
#include "meat_buffer.h"

#define PRODUCT_ID "MEATLOAF CBM"

class iecDisk : public virtualDevice
{
private:
    //MediaType *_disk = nullptr;

    std::unique_ptr<MFile> _disk; // Always points to current directory/image
    std::string _file;         // Always points to current or last loaded file

    // Named Channel functions
    std::shared_ptr<MStream> currentStream;
    bool registerStream (int mode);
    std::shared_ptr<MStream> retrieveStream ( void );
    bool closeStream ( bool close_all = false );

    // Directory
	uint16_t sendHeader(std::string header, std::string id);
	uint16_t sendLine(uint16_t blocks, char *text);
	uint16_t sendLine(uint16_t blocks, const char *format, ...);
	uint16_t sendFooter();
	void sendListing();

    // File
	bool sendFile();
	bool saveFile();

    struct _error_response
    {
        unsigned char errnum = 73;
        std::string msg = "CBM DOS V2.6 1541";
        unsigned char track = 0;
        unsigned char sector = 0;
    } error_response;

    void read();
    void write(bool verify);
    void format();

protected:
    device_state_t process(IECData *commanddata) override;
    void process_load();
    void process_save();
    void process_command();
    void process_file();

public:
    iecDisk();
    fujiHost *host;
    mediatype_t mount(FILE *f, const char *filename, uint32_t disksize, mediatype_t disk_type = MEDIATYPE_UNKNOWN);
    void unmount();
    bool write_blank(FILE *f, uint16_t sectorSize, uint16_t numSectors);

    //mediatype_t disktype() { return _disk == nullptr ? MEDIATYPE_UNKNOWN : _disk->_mediatype; };

    std::unordered_map<uint16_t, std::shared_ptr<MStream>> streams;

    ~iecDisk();
};

#endif

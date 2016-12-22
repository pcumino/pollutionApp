#include <cstdint>  // for std::uint64_t
#include <cstdlib>  // for std::exit
#include <iostream> // for std::cout, std::cerr

// Allow any format of input files (XML, PBF, ...)
#include <osmium/io/any_input.hpp>

// We want to use the handler interface
#include <osmium/handler.hpp>

// Utility class gives us access to memory usage information
#include <osmium/util/memory.hpp>

// For osmium::apply()
#include <osmium/visitor.hpp>

#include "ModJson.h"


using namespace std;

class NamesHandler : public osmium::handler::Handler {

	void output_pubs(const osmium::OSMObject& object) {
		const osmium::TagList& tags = object.tags();

		if (tags.has_tag("pollution", "low")) {

			// Print name of the pub if it is set.
			const char* name = tags["name"];
			if (name) {
				cout << name << "\n";
			} else {
				cout << "pub with unknown name\n";
			}

			// Iterate over all tags finding those which start with "addr:"
			// and print them.
			for (const osmium::Tag& tag : tags) {
				if (!strncmp(tag.key(), "addr:", 5)) {
					cout << "  " << tag.key() << ": " << tag.value() << "\n";
				}
			}
		}
	}

public:

	// Nodes can be tagged amenity=pub.
	void node(const osmium::Node& node) {
		output_pubs(node);
	}
	ModJson jsontool;
		jsontool.setFile("sensorData.json");
		vector< vector<string> > vec = jsontool.getVecList();
	// Ways can be tagged amenity=pub, too (typically buildings).
	void way(const osmium::Way& way) {
		output_pubs(way);
	}

}; // class NamesHandler

struct CountHandler : public osmium::handler::Handler {

	uint64_t nodes     = 0;
	uint64_t ways      = 0;
	uint64_t relations = 0;

	// This callback is called by osmium::apply for each node in the data.
	void node(const osmium::Node&) noexcept {
		++nodes;
	}

	// This callback is called by osmium::apply for each way in the data.
	void way(const osmium::Way&) noexcept {
		++ways;
	}

	// This callback is called by osmium::apply for each relation in the data.
	void relation(const osmium::Relation&) noexcept {
		++relations;
	}

}; // struct CountHandler

int main(int argc, char* argv[]) {
	if (argc != 2) {
		cerr << "Usage: " << argv[0] << " OSMFILE\n";
		exit(1);
	}

	ModJson jsontool;
	jsontool.setFile("sensorata.json");
	vector< vector<string> > vec = jsontool.getVecList();

	// The Reader is initialized here with an osmium::io::File, but could
	// also be directly initialized with a file name.
	osmium::io::File input_file{argv[1]};
	osmium::io::Reader reader{input_file};

	CountHandler handler;
	osmium::apply(reader, handler);

	// You do not have to close the Reader explicitly, but because the
	// destructor can't throw, you will not see any errors otherwise.
	reader.close();

	cout << "Nodes\t=\t" << handler.nodes << endl;
	cout << "Ways\t=\t" << handler.ways << endl;
	cout << "Rel\t=\t" << handler.relations << endl;

	osmium::MemoryUsage memory;

	cout << "Mem used = " << memory.peak() << "MBytes" << endl;

	NamesHandler names_handler;
	osmium::io::Reader reader2{argv[1], osmium::osm_entity_bits::node | osmium::osm_entity_bits::way};
	osmium::apply(reader2, names_handler);

}
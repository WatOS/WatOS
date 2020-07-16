#pragma once

struct cpuid_info_data {
	union {
		struct {
			unsigned stepping : 4;
			unsigned model : 4;
			unsigned family : 4;
			unsigned type : 2;
			unsigned r1 : 2;
			unsigned ext_model : 4;
			unsigned ext_family : 8;
		} ver;
		uint32_t ver_int;
	};

	unsigned real_model;
	unsigned real_family;

	union {
		struct {
			unsigned brand_idx : 8;
			unsigned cflush_line_size : 8;
			unsigned max_logical_ids : 8;
			unsigned local_apic_id : 8;
		} extra;
		uint32_t extra_int;
	};

	union {
		struct {
			bool fpu : 1;
			bool vme : 1;
			bool de : 1;
			bool pse : 1;
			bool tsc : 1;
			bool msr : 1;
			bool pae : 1;
			bool mce : 1;
			bool cx8 : 1;
			bool apic : 1;
		} flags;
		struct {
			uint32_t flags_1;
			uint32_t flags_2;
		} flags_int;
	};
};

uint32_t cpuid_vendor(char * result);
struct cpuid_info_data cpuid_info(void);

#pragma once

#include <glib.h>

#include <config_file.h>

typedef struct {
	gchar* slotclass;
	RaucChecksum checksum;
	gchar* filename;
} RaucImage;

typedef struct {
	gchar* slotclass;
	RaucChecksum checksum;
	gchar* filename;
	gchar* destname;
} RaucFile;

typedef struct {
	gchar *update_compatible;
	gchar *update_version;

	gchar *keyring;

	gchar *handler_name;

	GList *images;
	GList *files;
} RaucManifest;

gboolean load_manifest_mem(GBytes *mem, RaucManifest **manifest);
gboolean load_manifest_file(const gchar *filename, RaucManifest **manifest);
gboolean save_manifest_file(const gchar *filename, RaucManifest *manifest);
void free_manifest(RaucManifest *manifest);

gboolean update_manifest(const gchar *dir, gboolean signature);

/**
 * Loads and verifies manifest in directory.
 *
 * The manifest itself must be named 'manifest.raucm'.
 * An optional signature file must be named 'manifest.raucm.sig'
 *
 * @param dir Directory the manifest is located in
 * @param output Returns newly allocated manifest if RaucManifest pointerpointer
 *        is provided.
 *        If output is NULL, manifest will be freed an nothing returned.
 * @param signature If true, manifest ist validated using the provided signature
 *        file.
 *        If false, no further signature validation is performed.
 *
 * @return True if successful, False if not sucessful
 */
gboolean verify_manifest(const gchar *dir, RaucManifest **output, gboolean signature);

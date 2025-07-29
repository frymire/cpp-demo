
#pragma once

// It's okay to #include this into multiple files, because you're just
// copy-pasting the text of the code into each, and the static keyword
// limits the scope of each copied declaration to the separate files.
static int s_variable_in_header = 3;

#! /usr/bin/perl

use warnings;
use strict;

my $dir = `ls datasets`;

my @files = split('\n', $dir);

my $numFiles = @files;

for (my $i = 0; $i < $numFiles; $i++){
	print $files[$i] . ", ";
}

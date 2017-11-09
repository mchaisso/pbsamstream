This program is meant to be an interface between alignment methods and PacBio's handling of quality values, so that any aligner that can output in SAM will produce data compatible with the quiver/arrow consensus modules. Aligners should consume sequences as unaligned reads from a SAM file, and output the aligned read with soft clipping, along with any optional tags included in the original alignment.

This example uses a modified blasr that outputs the optional tags using a `-passthrough` flag.

`samtools view -h m54019_171021_174649.subreads.bam | ~/projects/mcblasr/blasr/alignment/bin/blasr /dev/stdin ecoli_k12.fasta -clipping soft -passthrough -streaming -fileType sam -m 4 -out /dev/stdout -bestn 1 -sam -minMatch 18 -advanceExactMatches 10  | head -20000 | ~/projects/pbsamstream/pbsamstream - | samtools view -bS - | samtools sort -T tmp -o aligned.passhtrough.bam`


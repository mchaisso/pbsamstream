#ifndef SAM_FLAG_H_
#define SAM_FLAG_H_

inline bool IsMultipleSegment(unsigned int flag) { return flag & 0x1; }

inline bool AllSegmentsMapped(unsigned int flag) { return flag & 0x2; }

inline bool SegmentUnmapped(unsigned int flag) { return flag & 0x4; }

inline bool NextUnmapped(unsigned int flag) { return flag & 0x8; }

inline bool IsReverseComplement(unsigned int flag) { return flag & 0x10; }

inline bool IsNextReverseComplement(unsigned int flag) { return flag & 0x20; }

inline bool IsSegemntFirst(unsigned int flag) { return flag & 0x40; }

inline bool IsSegmentLast(unsigned int flag) { return flag & 0x80; }

inline bool IsSecondaryAlignment(unsigned int flag) { return flag & 0x100; }

inline bool IsNotPassedQuality(unsigned int flag) { return flag & 0x200; }

inline bool IsDuplicate(unsigned int flag) { return flag & 0x400; }

#endif

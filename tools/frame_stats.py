import argparse
import json
import statistics
from pathlib import Path


def frame_stats(text, after=0):
    presents = set()
    for line in text.splitlines():
        fields = line.split()
        if len(fields) != 3:
            continue
        try:
            timestamp = int(fields[1])
        except ValueError:
            continue
        if after < timestamp < 9223372036854775807:
            presents.add(timestamp)
    presents = sorted(presents)
    intervals = [(b - a) / 1_000_000 for a, b in zip(presents, presents[1:])]
    if not intervals:
        return {"valid": False, "frames": len(presents)}
    ordered = sorted(intervals)
    duration = (presents[-1] - presents[0]) / 1_000_000_000
    return {
        "valid": True,
        "frames": len(presents),
        "duration_seconds": duration,
        "fps_mean": len(intervals) / duration,
        "median_frame_ms": statistics.median(intervals),
        "p90_frame_ms": ordered[min(len(ordered) - 1, int(len(ordered) * 0.9))],
        "max_frame_ms": max(intervals),
        "first_present_ns": presents[0],
        "last_present_ns": presents[-1],
    }


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("input", type=Path)
    parser.add_argument("--after", type=int, default=0)
    args = parser.parse_args()
    print(json.dumps(frame_stats(args.input.read_text(encoding="utf-8-sig"), args.after), indent=2))

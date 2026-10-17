#include <cassert>
#include <cstdio>
#include <deque>
#include <vector>
#include "common/range_sets.inc"

struct Model {
    Common::RangeSet<u64> dirty;
    Common::RangeSet<u64> uncommitted;
    std::deque<Common::RangeSet<u64>> accumulated;
    Common::OverlapRangeSet<u64> downloads;

    void Retire(bool protect) {
        downloads.Subtract(1000, 64, [&](u64 start, u64 end) {
            dirty.Subtract(start, end - start);
            if (protect) {
                auto preserve = [&](u64 a, u64 b) { dirty.Add(a, b - a); };
                uncommitted.ForEachInRange(start, end - start, preserve);
                for (const auto& pending : accumulated) {
                    pending.ForEachInRange(start, end - start, preserve);
                }
            }
        });
    }

    bool IsDirty(u64 address) const {
        bool result = false;
        dirty.ForEachInRange(address, 1, [&](u64, u64) { result = true; });
        return result;
    }

    void OldSnapshot() {
        dirty.Add(1000, 64);
        downloads.Add(1000, 64);
    }
};

int main() {
    {
        Model baseline;
        baseline.OldSnapshot();
        baseline.uncommitted.Add(1016, 16);
        baseline.Retire(false);
        assert(!baseline.IsDirty(1020));
    }
    {
        Model fixed;
        fixed.OldSnapshot();
        fixed.uncommitted.Add(1016, 16);
        fixed.Retire(true);
        assert(!fixed.IsDirty(1000));
        assert(fixed.IsDirty(1016) && fixed.IsDirty(1031));
        assert(!fixed.IsDirty(1032));
    }
    {
        Model fixed;
        fixed.OldSnapshot();
        fixed.uncommitted.Add(1016, 16);
        fixed.accumulated.emplace_back(std::move(fixed.uncommitted));
        fixed.Retire(true);
        assert(fixed.IsDirty(1020) && !fixed.IsDirty(1040));
    }
    {
        Model fixed;
        fixed.OldSnapshot();
        fixed.downloads.Add(1000, 64);
        fixed.Retire(true);
        assert(fixed.IsDirty(1020));
        fixed.Retire(true);
        assert(!fixed.IsDirty(1020));
    }
    {
        Model fixed;
        fixed.OldSnapshot();
        fixed.uncommitted.Add(1016, 16);
        fixed.downloads.DeleteAll(1000, 64);
        fixed.uncommitted.Subtract(1000, 64);
        fixed.dirty.Subtract(1000, 64);
        fixed.Retire(true);
        assert(!fixed.IsDirty(1020));
    }
    {
        Model fixed;
        fixed.OldSnapshot();
        fixed.dirty.Add(2000, 8);
        fixed.uncommitted.Add(2000, 8);
        fixed.Retire(true);
        assert(fixed.IsDirty(2000) && !fixed.IsDirty(1020));
    }
    std::puts("PASS: old snapshot, newer pending writes, accumulated writes, overlapping snapshots, CPU invalidation, disjoint writes");
}

#pragma once

namespace MaikoDev {
    namespace Arc {
        namespace Commands {
            enum class CommandType {
                UNDEFINED,
                Init,
                Add,
                Move,
                Restore,
                Remove,
                Bisect,
                Diff,
                Grep,
                Log,
                Show,
                Status,
                Branch,
                Commit,
                Merge,
                Rebase,
                Reset,
                Switch,
                Tag,
                Fetch,
                Pull,
                Push,
            };
        }
    }
}
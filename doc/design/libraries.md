# Libraries

| Name                     | Description |
|--------------------------|-------------|
| *libx1coin_cli*         | RPC client functionality used by *x1coin-cli* executable |
| *libx1coin_common*      | Home for common functionality shared by different executables and libraries. Similar to *libx1coin_util*, but higher-level (see [Dependencies](#dependencies)). |
| *libx1coin_consensus*   | Stable, backwards-compatible consensus functionality used by *libx1coin_node* and *libx1coin_wallet* and also exposed as a [shared library](../shared-libraries.md). |
| *libx1coinconsensus*    | Shared library build of static *libx1coin_consensus* library |
| *libx1coin_kernel*      | Consensus engine and support library used for validation by *libx1coin_node* and also exposed as a [shared library](../shared-libraries.md). |
| *libx1coinqt*           | GUI functionality used by *x1coin-qt* and *x1coin-gui* executables |
| *libx1coin_ipc*         | IPC functionality used by *x1coin-node*, *x1coin-wallet*, *x1coin-gui* executables to communicate when [`--enable-multiprocess`](multiprocess.md) is used. |
| *libx1coin_node*        | P2P and RPC server functionality used by *x1coind* and *x1coin-qt* executables. |
| *libx1coin_util*        | Home for common functionality shared by different executables and libraries. Similar to *libx1coin_common*, but lower-level (see [Dependencies](#dependencies)). |
| *libx1coin_wallet*      | Wallet functionality used by *x1coind* and *x1coin-wallet* executables. |
| *libx1coin_wallet_tool* | Lower-level wallet functionality used by *x1coin-wallet* executable. |
| *libx1coin_zmq*         | [ZeroMQ](../zmq.md) functionality used by *x1coind* and *x1coin-qt* executables. |

## Conventions

- Most libraries are internal libraries and have APIs which are completely unstable! There are few or no restrictions on backwards compatibility or rules about external dependencies. Exceptions are *libx1coin_consensus* and *libx1coin_kernel* which have external interfaces documented at [../shared-libraries.md](../shared-libraries.md).

- Generally each library should have a corresponding source directory and namespace. Source code organization is a work in progress, so it is true that some namespaces are applied inconsistently, and if you look at [`libx1coin_*_SOURCES`](../../src/Makefile.am) lists you can see that many libraries pull in files from outside their source directory. But when working with libraries, it is good to follow a consistent pattern like:

  - *libx1coin_node* code lives in `src/node/` in the `node::` namespace
  - *libx1coin_wallet* code lives in `src/wallet/` in the `wallet::` namespace
  - *libx1coin_ipc* code lives in `src/ipc/` in the `ipc::` namespace
  - *libx1coin_util* code lives in `src/util/` in the `util::` namespace
  - *libx1coin_consensus* code lives in `src/consensus/` in the `Consensus::` namespace

## Dependencies

- Libraries should minimize what other libraries they depend on, and only reference symbols following the arrows shown in the dependency graph below:

<table><tr><td>

```mermaid

%%{ init : { "flowchart" : { "curve" : "basis" }}}%%

graph TD;

x1coin-cli[x1coin-cli]-->libx1coin_cli;

x1coind[x1coind]-->libx1coin_node;
x1coind[x1coind]-->libx1coin_wallet;

x1coin-qt[x1coin-qt]-->libx1coin_node;
x1coin-qt[x1coin-qt]-->libx1coinqt;
x1coin-qt[x1coin-qt]-->libx1coin_wallet;

x1coin-wallet[x1coin-wallet]-->libx1coin_wallet;
x1coin-wallet[x1coin-wallet]-->libx1coin_wallet_tool;

libx1coin_cli-->libx1coin_util;
libx1coin_cli-->libx1coin_common;

libx1coin_common-->libx1coin_consensus;
libx1coin_common-->libx1coin_util;

libx1coin_kernel-->libx1coin_consensus;
libx1coin_kernel-->libx1coin_util;

libx1coin_node-->libx1coin_consensus;
libx1coin_node-->libx1coin_kernel;
libx1coin_node-->libx1coin_common;
libx1coin_node-->libx1coin_util;

libx1coinqt-->libx1coin_common;
libx1coinqt-->libx1coin_util;

libx1coin_wallet-->libx1coin_common;
libx1coin_wallet-->libx1coin_util;

libx1coin_wallet_tool-->libx1coin_wallet;
libx1coin_wallet_tool-->libx1coin_util;

classDef bold stroke-width:2px, font-weight:bold, font-size: smaller;
class x1coin-qt,x1coind,x1coin-cli,x1coin-wallet bold
```
</td></tr><tr><td>

**Dependency graph**. Arrows show linker symbol dependencies. *Consensus* lib depends on nothing. *Util* lib is depended on by everything. *Kernel* lib depends only on consensus and util.

</td></tr></table>

- The graph shows what _linker symbols_ (functions and variables) from each library other libraries can call and reference directly, but it is not a call graph. For example, there is no arrow connecting *libx1coin_wallet* and *libx1coin_node* libraries, because these libraries are intended to be modular and not depend on each other's internal implementation details. But wallet code is still able to call node code indirectly through the `interfaces::Chain` abstract class in [`interfaces/chain.h`](../../src/interfaces/chain.h) and node code calls wallet code through the `interfaces::ChainClient` and `interfaces::Chain::Notifications` abstract classes in the same file. In general, defining abstract classes in [`src/interfaces/`](../../src/interfaces/) can be a convenient way of avoiding unwanted direct dependencies or circular dependencies between libraries.

- *libx1coin_consensus* should be a standalone dependency that any library can depend on, and it should not depend on any other libraries itself.

- *libx1coin_util* should also be a standalone dependency that any library can depend on, and it should not depend on other internal libraries.

- *libx1coin_common* should serve a similar function as *libx1coin_util* and be a place for miscellaneous code used by various daemon, GUI, and CLI applications and libraries to live. It should not depend on anything other than *libx1coin_util* and *libx1coin_consensus*. The boundary between _util_ and _common_ is a little fuzzy but historically _util_ has been used for more generic, lower-level things like parsing hex, and _common_ has been used for x1coin-specific, higher-level things like parsing base58. The difference between util and common is mostly important because *libx1coin_kernel* is not supposed to depend on *libx1coin_common*, only *libx1coin_util*. In general, if it is ever unclear whether it is better to add code to *util* or *common*, it is probably better to add it to *common* unless it is very generically useful or useful particularly to include in the kernel.


- *libx1coin_kernel* should only depend on *libx1coin_util* and *libx1coin_consensus*.

- The only thing that should depend on *libx1coin_kernel* internally should be *libx1coin_node*. GUI and wallet libraries *libx1coinqt* and *libx1coin_wallet* in particular should not depend on *libx1coin_kernel* and the unneeded functionality it would pull in, like block validation. To the extent that GUI and wallet code need scripting and signing functionality, they should be get able it from *libx1coin_consensus*, *libx1coin_common*, and *libx1coin_util*, instead of *libx1coin_kernel*.

- GUI, node, and wallet code internal implementations should all be independent of each other, and the *libx1coinqt*, *libx1coin_node*, *libx1coin_wallet* libraries should never reference each other's symbols. They should only call each other through [`src/interfaces/`](`../../src/interfaces/`) abstract interfaces.

## Work in progress

- Validation code is moving from *libx1coin_node* to *libx1coin_kernel* as part of [The libx1coinkernel Project #24303](https://github.com/bLeYeNk/X1Coin/issues/24303)
- Source code organization is discussed in general in [Library source code organization #15732](https://github.com/bLeYeNk/X1Coin/issues/15732)

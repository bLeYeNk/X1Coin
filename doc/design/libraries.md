# Libraries

| Name                     | Description |
|--------------------------|-------------|
| *libbitcoins_cli*         | RPC client functionality used by *bitcoins-cli* executable |
| *libbitcoins_common*      | Home for common functionality shared by different executables and libraries. Similar to *libbitcoins_util*, but higher-level (see [Dependencies](#dependencies)). |
| *libbitcoins_consensus*   | Stable, backwards-compatible consensus functionality used by *libbitcoins_node* and *libbitcoins_wallet* and also exposed as a [shared library](../shared-libraries.md). |
| *libbitcoinsconsensus*    | Shared library build of static *libbitcoins_consensus* library |
| *libbitcoins_kernel*      | Consensus engine and support library used for validation by *libbitcoins_node* and also exposed as a [shared library](../shared-libraries.md). |
| *libbitcoinsqt*           | GUI functionality used by *bitcoins-qt* and *bitcoins-gui* executables |
| *libbitcoins_ipc*         | IPC functionality used by *bitcoins-node*, *bitcoins-wallet*, *bitcoins-gui* executables to communicate when [`--enable-multiprocess`](multiprocess.md) is used. |
| *libbitcoins_node*        | P2P and RPC server functionality used by *bitcoinsd* and *bitcoins-qt* executables. |
| *libbitcoins_util*        | Home for common functionality shared by different executables and libraries. Similar to *libbitcoins_common*, but lower-level (see [Dependencies](#dependencies)). |
| *libbitcoins_wallet*      | Wallet functionality used by *bitcoinsd* and *bitcoins-wallet* executables. |
| *libbitcoins_wallet_tool* | Lower-level wallet functionality used by *bitcoins-wallet* executable. |
| *libbitcoins_zmq*         | [ZeroMQ](../zmq.md) functionality used by *bitcoinsd* and *bitcoins-qt* executables. |

## Conventions

- Most libraries are internal libraries and have APIs which are completely unstable! There are few or no restrictions on backwards compatibility or rules about external dependencies. Exceptions are *libbitcoins_consensus* and *libbitcoins_kernel* which have external interfaces documented at [../shared-libraries.md](../shared-libraries.md).

- Generally each library should have a corresponding source directory and namespace. Source code organization is a work in progress, so it is true that some namespaces are applied inconsistently, and if you look at [`libbitcoins_*_SOURCES`](../../src/Makefile.am) lists you can see that many libraries pull in files from outside their source directory. But when working with libraries, it is good to follow a consistent pattern like:

  - *libbitcoins_node* code lives in `src/node/` in the `node::` namespace
  - *libbitcoins_wallet* code lives in `src/wallet/` in the `wallet::` namespace
  - *libbitcoins_ipc* code lives in `src/ipc/` in the `ipc::` namespace
  - *libbitcoins_util* code lives in `src/util/` in the `util::` namespace
  - *libbitcoins_consensus* code lives in `src/consensus/` in the `Consensus::` namespace

## Dependencies

- Libraries should minimize what other libraries they depend on, and only reference symbols following the arrows shown in the dependency graph below:

<table><tr><td>

```mermaid

%%{ init : { "flowchart" : { "curve" : "basis" }}}%%

graph TD;

bitcoins-cli[bitcoins-cli]-->libbitcoins_cli;

bitcoinsd[bitcoinsd]-->libbitcoins_node;
bitcoinsd[bitcoinsd]-->libbitcoins_wallet;

bitcoins-qt[bitcoins-qt]-->libbitcoins_node;
bitcoins-qt[bitcoins-qt]-->libbitcoinsqt;
bitcoins-qt[bitcoins-qt]-->libbitcoins_wallet;

bitcoins-wallet[bitcoins-wallet]-->libbitcoins_wallet;
bitcoins-wallet[bitcoins-wallet]-->libbitcoins_wallet_tool;

libbitcoins_cli-->libbitcoins_util;
libbitcoins_cli-->libbitcoins_common;

libbitcoins_common-->libbitcoins_consensus;
libbitcoins_common-->libbitcoins_util;

libbitcoins_kernel-->libbitcoins_consensus;
libbitcoins_kernel-->libbitcoins_util;

libbitcoins_node-->libbitcoins_consensus;
libbitcoins_node-->libbitcoins_kernel;
libbitcoins_node-->libbitcoins_common;
libbitcoins_node-->libbitcoins_util;

libbitcoinsqt-->libbitcoins_common;
libbitcoinsqt-->libbitcoins_util;

libbitcoins_wallet-->libbitcoins_common;
libbitcoins_wallet-->libbitcoins_util;

libbitcoins_wallet_tool-->libbitcoins_wallet;
libbitcoins_wallet_tool-->libbitcoins_util;

classDef bold stroke-width:2px, font-weight:bold, font-size: smaller;
class bitcoins-qt,bitcoinsd,bitcoins-cli,bitcoins-wallet bold
```
</td></tr><tr><td>

**Dependency graph**. Arrows show linker symbol dependencies. *Consensus* lib depends on nothing. *Util* lib is depended on by everything. *Kernel* lib depends only on consensus and util.

</td></tr></table>

- The graph shows what _linker symbols_ (functions and variables) from each library other libraries can call and reference directly, but it is not a call graph. For example, there is no arrow connecting *libbitcoins_wallet* and *libbitcoins_node* libraries, because these libraries are intended to be modular and not depend on each other's internal implementation details. But wallet code is still able to call node code indirectly through the `interfaces::Chain` abstract class in [`interfaces/chain.h`](../../src/interfaces/chain.h) and node code calls wallet code through the `interfaces::ChainClient` and `interfaces::Chain::Notifications` abstract classes in the same file. In general, defining abstract classes in [`src/interfaces/`](../../src/interfaces/) can be a convenient way of avoiding unwanted direct dependencies or circular dependencies between libraries.

- *libbitcoins_consensus* should be a standalone dependency that any library can depend on, and it should not depend on any other libraries itself.

- *libbitcoins_util* should also be a standalone dependency that any library can depend on, and it should not depend on other internal libraries.

- *libbitcoins_common* should serve a similar function as *libbitcoins_util* and be a place for miscellaneous code used by various daemon, GUI, and CLI applications and libraries to live. It should not depend on anything other than *libbitcoins_util* and *libbitcoins_consensus*. The boundary between _util_ and _common_ is a little fuzzy but historically _util_ has been used for more generic, lower-level things like parsing hex, and _common_ has been used for bitcoins-specific, higher-level things like parsing base58. The difference between util and common is mostly important because *libbitcoins_kernel* is not supposed to depend on *libbitcoins_common*, only *libbitcoins_util*. In general, if it is ever unclear whether it is better to add code to *util* or *common*, it is probably better to add it to *common* unless it is very generically useful or useful particularly to include in the kernel.


- *libbitcoins_kernel* should only depend on *libbitcoins_util* and *libbitcoins_consensus*.

- The only thing that should depend on *libbitcoins_kernel* internally should be *libbitcoins_node*. GUI and wallet libraries *libbitcoinsqt* and *libbitcoins_wallet* in particular should not depend on *libbitcoins_kernel* and the unneeded functionality it would pull in, like block validation. To the extent that GUI and wallet code need scripting and signing functionality, they should be get able it from *libbitcoins_consensus*, *libbitcoins_common*, and *libbitcoins_util*, instead of *libbitcoins_kernel*.

- GUI, node, and wallet code internal implementations should all be independent of each other, and the *libbitcoinsqt*, *libbitcoins_node*, *libbitcoins_wallet* libraries should never reference each other's symbols. They should only call each other through [`src/interfaces/`](`../../src/interfaces/`) abstract interfaces.

## Work in progress

- Validation code is moving from *libbitcoins_node* to *libbitcoins_kernel* as part of [The libbitcoinskernel Project #24303](https://github.com/bitcoins/bitcoins/issues/24303)
- Source code organization is discussed in general in [Library source code organization #15732](https://github.com/bitcoins/bitcoins/issues/15732)

/*
 *  Copyright (c) 2018-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the BSD-style license found in the
 *  LICENSE file in the root directory of this source tree. An additional grant
 *  of patent rights can be found in the PATENTS file in the same directory.
 *
 */
#pragma once
#include <folly/Synchronized.h>
#include "eden/fs/sqlite/Sqlite.h"
#include "eden/fs/store/LocalStore.h"

namespace facebook {
namespace eden {

/** An implementation of LocalStore that stores values in Sqlite.
 * SqliteLocalStore is thread safe, allowing reads and writes from
 * any thread.
 * */
class SqliteLocalStore : public LocalStore {
 public:
  explicit SqliteLocalStore(
      AbsolutePathPiece pathToDb,
      std::shared_ptr<ReloadableConfig> config = nullptr);
  void close() override;
  void clearKeySpace(KeySpace keySpace) override;
  void compactKeySpace(KeySpace keySpace) override;
  StoreResult get(LocalStore::KeySpace keySpace, folly::ByteRange key)
      const override;
  bool hasKey(LocalStore::KeySpace keySpace, folly::ByteRange key)
      const override;
  void put(
      LocalStore::KeySpace keySpace,
      folly::ByteRange key,
      folly::ByteRange value) override;
  std::unique_ptr<LocalStore::WriteBatch> beginWrite(
      size_t bufSize = 0) override;

 private:
  mutable SqliteDatabase db_;
};

} // namespace eden
} // namespace facebook

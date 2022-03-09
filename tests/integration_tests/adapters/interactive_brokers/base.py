import asyncio
import os
from unittest.mock import patch

from nautilus_trader.adapters.interactive_brokers.config import InteractiveBrokersDataClientConfig
from nautilus_trader.adapters.interactive_brokers.config import InteractiveBrokersExecClientConfig
from nautilus_trader.adapters.interactive_brokers.factories import (
    InteractiveBrokersLiveDataClientFactory,
)
from nautilus_trader.adapters.interactive_brokers.factories import (
    InteractiveBrokersLiveExecClientFactory,
)
from nautilus_trader.cache.cache import Cache
from nautilus_trader.common.clock import LiveClock
from nautilus_trader.common.enums import LogLevel
from nautilus_trader.common.logging import LiveLogger
from nautilus_trader.msgbus.bus import MessageBus
from tests.test_kit.mocks.cache_database import MockCacheDatabase
from tests.test_kit.stubs.identifiers import TestIdStubs


class InteractiveBrokersTestBase:
    def setup(self):
        os.environ.update(
            {
                "TWS_USERNAME": "username",
                "TWS_PASSWORD": "password",
            }
        )
        # Fixture Setup
        self.loop = asyncio.get_event_loop()
        self.clock = LiveClock()
        self.logger = LiveLogger(
            loop=self.loop,
            clock=self.clock,
            level_stdout=LogLevel.DEBUG,
        )

        self.trader_id = TestIdStubs.trader_id()
        self.strategy_id = TestIdStubs.strategy_id()
        self.account_id = TestIdStubs.account_id()

        self.msgbus = MessageBus(
            trader_id=self.trader_id,
            clock=self.clock,
            logger=self.logger,
        )

        self.cache_db = MockCacheDatabase(
            logger=self.logger,
        )

        self.cache = Cache(
            database=self.cache_db,
            logger=self.logger,
        )
        with patch("nautilus_trader.adapters.interactive_brokers.factories.get_cached_ib_client"):
            self.data_client = InteractiveBrokersLiveDataClientFactory.create(
                loop=self.loop,
                name="IB",
                config=InteractiveBrokersDataClientConfig(  # noqa: S106
                    username="test", password="test"
                ),
                msgbus=self.msgbus,
                cache=self.cache,
                clock=self.clock,
                logger=self.logger,
            )
        with patch("nautilus_trader.adapters.interactive_brokers.factories.get_cached_ib_client"):
            self.exec_client = InteractiveBrokersLiveExecClientFactory.create(
                loop=self.loop,
                name="IB",
                config=InteractiveBrokersExecClientConfig(  # noqa: S106
                    username="test", password="test"
                ),
                msgbus=self.msgbus,
                cache=self.cache,
                clock=self.clock,
                logger=self.logger,
            )

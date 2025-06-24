// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <coreTest/ObservableTest.h>

#include <feather-tk/core/Assert.h>
#include <feather-tk/core/ObservableList.h>
#include <feather-tk/core/ObservableMap.h>
#include <feather-tk/core/ObservableValue.h>

namespace feather_tk
{
    namespace core_test
    {
        ObservableTest::ObservableTest(const std::shared_ptr<Context>& context) :
            ITest(context, "feather_tk::core_test::ObservableTest")
        {}

        ObservableTest::~ObservableTest()
        {}

        std::shared_ptr<ObservableTest> ObservableTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<ObservableTest>(new ObservableTest(context));
        }
        
        void ObservableTest::run()
        {
            _value();
            _list();
            _map();
        }
        
        void ObservableTest::_value()
        {
            auto ovalue = ObservableValue<bool>::create();
            ovalue = ObservableValue<bool>::create(false);
            FEATHER_TK_ASSERT(!ovalue->get());                
            {
                auto observer = ValueObserver<bool>::create(ovalue, [](bool) {});
                FEATHER_TK_ASSERT(ovalue->getObserversCount());                    
                {
                    bool value = false;
                    auto observer1 = ValueObserver<bool>::create(
                        ovalue,
                        [&value](bool v)
                        {
                            value = v;
                        });
                    FEATHER_TK_ASSERT(ovalue->setIfChanged(true));
                    FEATHER_TK_ASSERT(!ovalue->setIfChanged(true));
                    FEATHER_TK_ASSERT(value);
                    FEATHER_TK_ASSERT(ovalue->setIfChanged(false));
                    FEATHER_TK_ASSERT(!value);
                    ovalue->setAlways(false);
                    FEATHER_TK_ASSERT(!value);
                    ovalue->setAlways(true);
                    FEATHER_TK_ASSERT(value);
                }
            }
            FEATHER_TK_ASSERT(!ovalue->getObserversCount());
        }

        void ObservableTest::_list()
        {
            auto olist = ObservableList<int>::create();
            std::vector<int> list = { 0, 0 };
            olist = ObservableList<int>::create(list);
            FEATHER_TK_ASSERT(list == olist->get());                
            {
                auto observer = ListObserver<int>::create(
                    olist,
                    [](const std::vector<int>&) {});
                FEATHER_TK_ASSERT(olist->getObserversCount());                    
                {
                    auto observer1 = ListObserver<int>::create(
                        olist,
                        [&list](const std::vector<int>& value)
                        {
                            list = value;
                        });
                    FEATHER_TK_ASSERT(olist->setIfChanged({ 1, 0 }));
                    FEATHER_TK_ASSERT(!olist->setIfChanged({ 1, 0 }));
                    FEATHER_TK_ASSERT(!list.empty() && list[0]);
                    FEATHER_TK_ASSERT(olist->setIfChanged({ 0, 0 }));
                    FEATHER_TK_ASSERT(!list.empty() && 0 == list[0]);
                    olist->setAlways({ 0, 0 });
                    FEATHER_TK_ASSERT(!list.empty() && 0 == list[0]);
                    olist->setAlways({ 1, 0 });
                    FEATHER_TK_ASSERT(!list.empty() && 1 == list[0]);
                    olist->clear();
                    FEATHER_TK_ASSERT(list.empty());
                    olist->pushBack(1);
                    olist->pushBack(2);
                    FEATHER_TK_ASSERT(2 == olist->getSize());
                    FEATHER_TK_ASSERT(!olist->isEmpty());
                    FEATHER_TK_ASSERT(2 == olist->getItem(1));
                    FEATHER_TK_ASSERT(olist->contains(2));
                    FEATHER_TK_ASSERT(1 == olist->indexOf(2));
                    FEATHER_TK_ASSERT(!list.empty() && 1 == list[0]);
                    olist->setItem(0, 1);
                    olist->setItemOnlyIfChanged(0, 1);
                    olist->setItemOnlyIfChanged(0, 2);
                    olist->removeItem(1);
                    olist->removeItem(0);
                    FEATHER_TK_ASSERT(list.empty());
                }
            }
            FEATHER_TK_ASSERT(!olist->getObserversCount());
        }
        
        void ObservableTest::_map()
        {
            auto omap = ObservableMap<int, bool>::create();
            std::map<int, bool> map = { { 0, false }, { 0, false } };
            omap = ObservableMap<int, bool>::create(map);
            FEATHER_TK_ASSERT(map == omap->get());                
            {
                auto observer = MapObserver<int, bool>::create(
                    omap,
                    [](const std::map<int, bool>&) {});
                FEATHER_TK_ASSERT(omap->getObserversCount());                    
                {
                    auto observer1 = MapObserver<int, bool>::create(
                        omap,
                        [&map](const std::map<int, bool>& value)
                        {
                            map = value;
                        });
                    FEATHER_TK_ASSERT(omap->setIfChanged({ { 0, true }, { 1, false } }));
                    FEATHER_TK_ASSERT(!omap->setIfChanged({ { 0, true }, { 1, false } }));
                    FEATHER_TK_ASSERT(!map.empty() && map[0]);
                    FEATHER_TK_ASSERT(omap->setIfChanged({ { 0, false }, { 1, false } }));
                    FEATHER_TK_ASSERT(!map.empty() && !map[0]);
                    omap->setAlways({ { 0, false }, { 1, false } });
                    FEATHER_TK_ASSERT(!map.empty() && !map[0]);
                    omap->setAlways({ { 0, true }, { 1, false } });
                    FEATHER_TK_ASSERT(!map.empty() && map[0]);
                    omap->clear();
                    FEATHER_TK_ASSERT(map.empty());
                    omap->setItem(0, false);
                    omap->setItem(1, true);
                    FEATHER_TK_ASSERT(2 == omap->getSize());
                    FEATHER_TK_ASSERT(!omap->isEmpty());
                    FEATHER_TK_ASSERT(omap->hasKey(1));
                    FEATHER_TK_ASSERT(omap->getItem(1));
                    FEATHER_TK_ASSERT(!map.empty() && map[1]);
                    omap->setItem(1, false);
                    omap->setItemOnlyIfChanged(1, false);
                    omap->setItemOnlyIfChanged(1, true);
                }
            }
            FEATHER_TK_ASSERT(!omap->getObserversCount());
        }
    }
}


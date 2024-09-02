// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <coreTest/ObservableTest.h>

#include <dtk/core/Assert.h>
#include <dtk/core/ObservableList.h>
#include <dtk/core/ObservableMap.h>
#include <dtk/core/ObservableValue.h>

using namespace dtk::core;

namespace dtk
{
    namespace core_test
    {
        ObservableTest::ObservableTest(const std::shared_ptr<Context>& context) :
            ITest(context, "dtk::core_test::ObservableTest")
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
            DTK_ASSERT(!ovalue->get());                
            {
                auto observer = ValueObserver<bool>::create(ovalue, [](bool) {});
                DTK_ASSERT(ovalue->getObserversCount());                    
                {
                    bool value = false;
                    auto observer1 = ValueObserver<bool>::create(
                        ovalue,
                        [&value](bool v)
                        {
                            value = v;
                        });
                    DTK_ASSERT(ovalue->setIfChanged(true));
                    DTK_ASSERT(!ovalue->setIfChanged(true));
                    DTK_ASSERT(value);
                    DTK_ASSERT(ovalue->setIfChanged(false));
                    DTK_ASSERT(!value);
                    ovalue->setAlways(false);
                    DTK_ASSERT(!value);
                    ovalue->setAlways(true);
                    DTK_ASSERT(value);
                }
            }
            DTK_ASSERT(!ovalue->getObserversCount());
        }

        void ObservableTest::_list()
        {
            auto olist = ObservableList<int>::create();
            std::vector<int> list = { 0, 0 };
            olist = ObservableList<int>::create(list);
            DTK_ASSERT(list == olist->get());                
            {
                auto observer = ListObserver<int>::create(
                    olist,
                    [](const std::vector<int>&) {});
                DTK_ASSERT(olist->getObserversCount());                    
                {
                    auto observer1 = ListObserver<int>::create(
                        olist,
                        [&list](const std::vector<int>& value)
                        {
                            list = value;
                        });
                    DTK_ASSERT(olist->setIfChanged({ 1, 0 }));
                    DTK_ASSERT(!olist->setIfChanged({ 1, 0 }));
                    DTK_ASSERT(!list.empty() && list[0]);
                    DTK_ASSERT(olist->setIfChanged({ 0, 0 }));
                    DTK_ASSERT(!list.empty() && 0 == list[0]);
                    olist->setAlways({ 0, 0 });
                    DTK_ASSERT(!list.empty() && 0 == list[0]);
                    olist->setAlways({ 1, 0 });
                    DTK_ASSERT(!list.empty() && 1 == list[0]);
                    olist->clear();
                    DTK_ASSERT(list.empty());
                    olist->pushBack(1);
                    olist->pushBack(2);
                    DTK_ASSERT(2 == olist->getSize());
                    DTK_ASSERT(!olist->isEmpty());
                    DTK_ASSERT(2 == olist->getItem(1));
                    DTK_ASSERT(olist->contains(2));
                    DTK_ASSERT(1 == olist->indexOf(2));
                    DTK_ASSERT(!list.empty() && 1 == list[0]);
                    olist->setItem(0, 1);
                    olist->setItemOnlyIfChanged(0, 1);
                    olist->setItemOnlyIfChanged(0, 2);
                    olist->removeItem(1);
                    olist->removeItem(0);
                    DTK_ASSERT(list.empty());
                }
            }
            DTK_ASSERT(!olist->getObserversCount());
        }
        
        void ObservableTest::_map()
        {
            auto omap = ObservableMap<int, bool>::create();
            std::map<int, bool> map = { { 0, false }, { 0, false } };
            omap = ObservableMap<int, bool>::create(map);
            DTK_ASSERT(map == omap->get());                
            {
                auto observer = MapObserver<int, bool>::create(
                    omap,
                    [](const std::map<int, bool>&) {});
                DTK_ASSERT(omap->getObserversCount());                    
                {
                    auto observer1 = MapObserver<int, bool>::create(
                        omap,
                        [&map](const std::map<int, bool>& value)
                        {
                            map = value;
                        });
                    DTK_ASSERT(omap->setIfChanged({ { 0, true }, { 1, false } }));
                    DTK_ASSERT(!omap->setIfChanged({ { 0, true }, { 1, false } }));
                    DTK_ASSERT(!map.empty() && map[0]);
                    DTK_ASSERT(omap->setIfChanged({ { 0, false }, { 1, false } }));
                    DTK_ASSERT(!map.empty() && !map[0]);
                    omap->setAlways({ { 0, false }, { 1, false } });
                    DTK_ASSERT(!map.empty() && !map[0]);
                    omap->setAlways({ { 0, true }, { 1, false } });
                    DTK_ASSERT(!map.empty() && map[0]);
                    omap->clear();
                    DTK_ASSERT(map.empty());
                    omap->setItem(0, false);
                    omap->setItem(1, true);
                    DTK_ASSERT(2 == omap->getSize());
                    DTK_ASSERT(!omap->isEmpty());
                    DTK_ASSERT(omap->hasKey(1));
                    DTK_ASSERT(omap->getItem(1));
                    DTK_ASSERT(!map.empty() && map[1]);
                    omap->setItem(1, false);
                    omap->setItemOnlyIfChanged(1, false);
                    omap->setItemOnlyIfChanged(1, true);
                }
            }
            DTK_ASSERT(!omap->getObserversCount());
        }
    }
}


#include "StdInc.h"

#include "TaskComplexGetUpAndStandStill.h"

#include "TaskSimpleStandStill.h"
#include "TaskSimpleGetUp.h"

void CTaskComplexGetUpAndStandStill::InjectHooks() {
    RH_ScopedClass(CTaskComplexGetUpAndStandStill);
    RH_ScopedCategory("Tasks/TaskTypes");
    RH_ScopedInstall(Constructor, 0x678130);
    RH_ScopedInstall(CreateSubTask, 0x678170);
    // VTABLE
    RH_ScopedVirtualInstall(CreateFirstSubTask, 0x6782A0);
    RH_ScopedVirtualInstall(CreateNextSubTask, 0x678240);
    RH_ScopedVirtualInstall(ControlSubTask, 0x6782B0);
}

// 0x678130
CTaskComplexGetUpAndStandStill* CTaskComplexGetUpAndStandStill::Constructor() {
    this->CTaskComplexGetUpAndStandStill::CTaskComplexGetUpAndStandStill();
    return this;
}

// 0x6782A0
CTask* CTaskComplexGetUpAndStandStill::CreateFirstSubTask(CPed* ped) {
    return CreateFirstSubTask_Reversed(ped);
}

// 0x678240
CTask* CTaskComplexGetUpAndStandStill::CreateNextSubTask(CPed* ped) {
    return CreateNextSubTask_Reversed(ped);
}

// 0x6782B0
CTask* CTaskComplexGetUpAndStandStill::ControlSubTask(CPed* ped) {
    return ControlSubTask_Reversed(ped);
}

// 0x678170
CTask* CTaskComplexGetUpAndStandStill::CreateSubTask(eTaskType taskType) {
    switch (taskType) {
    case TASK_SIMPLE_GET_UP:
        return new CTaskSimpleGetUp();
    case TASK_SIMPLE_STAND_STILL:
        return new CTaskSimpleStandStill(0, false, false, 8.0F);
    case TASK_FINISHED:
    default:
        return nullptr;
    }
}

CTask* CTaskComplexGetUpAndStandStill::CreateFirstSubTask_Reversed(CPed* ped) {
    return CreateSubTask(TASK_SIMPLE_GET_UP);
}

CTask* CTaskComplexGetUpAndStandStill::CreateNextSubTask_Reversed(CPed* ped) {
    auto subTaskType = m_pSubTask->GetTaskType();

    if (subTaskType == TASK_SIMPLE_STAND_STILL)
        return CreateSubTask(TASK_FINISHED);

    if (subTaskType == TASK_SIMPLE_GET_UP) {
        auto pSubTask = reinterpret_cast<CTaskSimpleGetUp*>(m_pSubTask);

        if (pSubTask->m_bHasPedGotUp)
            return CreateSubTask(TASK_SIMPLE_STAND_STILL);
        else
            return CreateSubTask(TASK_FINISHED);
    }

    return nullptr;
}

CTask* CTaskComplexGetUpAndStandStill::ControlSubTask_Reversed(CPed* ped) {
    return m_pSubTask;
}

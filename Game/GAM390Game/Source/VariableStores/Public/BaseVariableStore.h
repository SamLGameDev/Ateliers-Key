// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
template<typename T>
class BaseVariableStore
{


public:


	/// <summary>
	/// set the current object to the input
	/// </summary>
	/// <param name="Object"></param>
	UFUNCTION(CallInEditor)
	virtual void SetObject(T Object);



	/// <summary>
	/// gets the current stored object.
	/// </summary>
	/// <returns></returns>
	UFUNCTION()
	virtual T GetRegisteredObject() const;

protected:
	UPROPERTY(VisibleAnywhere)
	T m_Object;


};


template<typename T>
inline void BaseVariableStore<T>::SetObject(T InObject)
{
	m_Object = InObject;
}

template<typename T>
inline T BaseVariableStore<T>::GetRegisteredObject() const
{
	return m_Object;
}
